#![no_std]
#![no_main]

/* Note:
This example is incomplete!
Ultimately, there are C files needed to support the STM32HAL patterns, for responsibilities for
the application-specific usage itself (e.g. clock setup).
TODO: Is there a way to have a separate build.rs for an example?
 */

// pick a panicking behavior
extern crate panic_halt; // you can put a breakpoint on `rust_begin_unwind` to catch panics
// extern crate panic_abort; // requires nightly
// extern crate panic_itm; // logs messages over ITM; requires ITM support
// extern crate panic_semihosting; // logs messages to the host stderr; requires a debugger

use cortex_m::asm;
use cortex_m_rt::entry;

extern crate cubeL4;

const RNG : *mut cubeL4::RNG_TypeDef = cubeL4::RNG_BASE as *mut cubeL4::RNG_TypeDef;

#[entry]
fn main() -> ! {
    asm::nop(); // To not have main optimize to abort in release mode, remove when you add code

    // let foo = cubeL4::RNG_BASE as *mut u32;

    let xRNG = cubeL4::RNG_HandleTypeDef {
        // Instance: cubeL4::RNG_BASE as *mut cubeL4::RNG_TypeDef,
        Instance : RNG,
        Lock: 0,
        State: 0,
        ErrorCode: 0,
        RandomNumber: 0
    };

    let raw = &xRNG as *const cubeL4::RNG_HandleTypeDef;

    unsafe {
        let hal_ret = cubeL4::HAL_RNG_Init(raw as *mut cubeL4::RNG_HandleTypeDef );
    }

    loop{};
}
