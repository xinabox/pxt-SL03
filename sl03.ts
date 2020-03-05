//% color=#444444 icon="\f018"
//% groups=['On start', 'Variables', 'Optional']
namespace SL03 {

    export enum state {
        //% block="OFF"
        OFF,
        //% block="ON"
        ON
    }

    /**
     * Initialize SL03 for Line Following
     */
    //%block="SL03 begin"
    //%shim=sl03::begin
    //% group="Optional"
    export function begin(): void {
        return;
    }

    /**
     * Turns IR LEDs ON or OFF
     * @param u logic state of the IR LEDs
     */
    //%block="SL03 infrared LED state %u"
    //%shim=sl03::irLedState
    //%advanced=true
    export function irLedState(u: state): void {
        return;
    }

    /**
     * Enables/ Disables the buffers (Active Low)
     * @param u logic state of the buffers
     */
    //%block="SL03 buffer state %u"
    //%shim=sl03::bufferState
    //%advanced=true
    export function bufferState(u: state): void {
        return;
    }

    /**
     * Returns IR receiver status as a byte
     */
    //%block="SL03 read input"
    //%shim=sl03::readInput
    //%group="Variables"
    //%advanced=true
    export function readInput(): number {
        return 1;
    }

    begin()
}
