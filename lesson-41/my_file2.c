/*.$file${.::my_file2.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: TimeBomb0.qm
* File:  ${.::my_file2.c}
*
* This code has been generated by QM 5.1.4 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${.::my_file2.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/* TimeBomb/Button with QP/C framework */
#include "qpc.h"  /* QP/C API */
#include "bsp.h"

Q_DEFINE_THIS_MODULE("my_file2") /* this module name for Q_ASSERT() */

/*.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*. Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.9.0 or higher required
#endif
/*.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$define${AOs} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::TimeBomb} ........................................................*/
/*.${AOs::TimeBomb::ctor} ..................................................*/
void TimeBomb_ctor(TimeBomb * const me) {
    QActive_ctor(&me->super, (QStateHandler)&TimeBomb_initial);
    QTimeEvt_ctorX(&me->te, &me->super, TIMEOUT_SIG, 0U);
}

/*.${AOs::TimeBomb::SM} ....................................................*/
QState TimeBomb_initial(TimeBomb * const me, void const * const par) {
    /*.${AOs::TimeBomb::SM::initial} */
    return Q_TRAN(&TimeBomb_wait4button);
}
/*.${AOs::TimeBomb::SM::defused} ...........................................*/
QState TimeBomb_defused(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::defused} */
        case Q_ENTRY_SIG: {
            BSP_ledBlueOn();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::defused::BUTTON2_PRESSED} */
        case BUTTON2_PRESSED_SIG: {
            status_ = Q_TRAN(&TimeBomb_armed);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${AOs::TimeBomb::SM::armed} .............................................*/
QState TimeBomb_armed(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::armed} */
        case Q_EXIT_SIG: {
            BSP_ledRedOff();
            BSP_ledGreenOff();
            BSP_ledBlueOff();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&TimeBomb_wait4button);
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::BUTTON2_PRESSED} */
        case BUTTON2_PRESSED_SIG: {
            status_ = Q_TRAN(&TimeBomb_defused);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${AOs::TimeBomb::SM::armed::wait4button} ................................*/
QState TimeBomb_wait4button(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::armed::wait4button} */
        case Q_ENTRY_SIG: {
            BSP_ledGreenOn();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::wait4button} */
        case Q_EXIT_SIG: {
            BSP_ledGreenOff();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::wait4button::BUTTON_PRESSED} */
        case BUTTON_PRESSED_SIG: {
            me->blink_ctr = 5U;
            status_ = Q_TRAN(&TimeBomb_blink);
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}
/*.${AOs::TimeBomb::SM::armed::blink} ......................................*/
QState TimeBomb_blink(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::armed::blink} */
        case Q_ENTRY_SIG: {
            BSP_ledRedOn();
            QTimeEvt_armX(&me->te, BSP_TICKS_PER_SEC/2, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::blink} */
        case Q_EXIT_SIG: {
            BSP_ledRedOff();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::blink::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&TimeBomb_pause);
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}
/*.${AOs::TimeBomb::SM::armed::pause} ......................................*/
QState TimeBomb_pause(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::armed::pause} */
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->te, BSP_TICKS_PER_SEC/2, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::TimeBomb::SM::armed::pause::TIMEOUT} */
        case TIMEOUT_SIG: {
            --me->blink_ctr;
            /*.${AOs::TimeBomb::SM::armed::pause::TIMEOUT::[blink_ctr>0]} */
            if (me->blink_ctr > 0U) {
                status_ = Q_TRAN(&TimeBomb_blink);
            }
            /*.${AOs::TimeBomb::SM::armed::pause::TIMEOUT::[else]} */
            else {
                status_ = Q_TRAN(&TimeBomb_boom);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}
/*.${AOs::TimeBomb::SM::armed::boom} .......................................*/
QState TimeBomb_boom(TimeBomb * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::TimeBomb::SM::armed::boom} */
        case Q_ENTRY_SIG: {
            BSP_ledRedOn();
            BSP_ledGreenOn();
            BSP_ledBlueOn();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&TimeBomb_armed);
            break;
        }
    }
    return status_;
}
/*.$enddef${AOs} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
