# cubeL4-rs

# Overview

This crate is an effort to make a minimal wrapper around the [STM32CubeL4]() vendor library, written in C, using
bindgen tooling, to ultimately provide this library and all of its features to embedded projects in Rust.

This crate has an assocaited [usage example](). I was not able to add that example to be internal to this crate, yet.  
Please clone it and build it separately.  
These crates together propose an initial workflow and pattern for using this C library on an STM32L4 microcontroller.

This project and the associated example has been tested, and produced a working ELF that can be flashed to an
STM32L475VG MCU and will run, using the hardware RNG to generate random numbers.

### Opinion

The concept here is to build a bridge to allow MCU's to use Rust-first projects, with the HAL needs delegated to a
known-good vendor implmention that supports everything the chip itself can do.

Yes, there are STM Rust crates. They are community-supported and not feature complete.  
Yes, the STM32HAL code has bugs and a slightly odd design pattern to it, with "MSP" callbacks.

The reality is that a huge amount of embedded projects will use a vendor library, like STM32HAL, along with other
major software components that are provided in plain C, e.g. FreeRTOS.  
I identify those are major needs.  
This project attempts to fulfill one of those needs.

Generally speaking, the workflow here could be extensible to any other vendor all-C MCU CSP/BSP library.

# Components

### STM32CubeL4 HAL

Several major directories from the [STM32CubeL4]() library are copied into this source tree.  
No major additions or movements are made. The DSP and NN libraries were removed for now.

### HAL conf header

The standard design of the STM32HAL requires an `stm32l4xx_hal_conf.h` file to be provided to configure the library.  
Things get complicated, since this config would actually be platform-dependent, so if you are targeting multiple
platforms from a single repo, now you have this header-only config dependency between a library and the application.

In this case:
- The default STM32L4 template is used here as the `stm32l4xx_hal_conf.h`
- Clock values are expected to be an issue BUT in the example usage, only the HSI (chip-specific) is used

### Bindings from bindgen

The bindgen output can be created by running `run_bindgen.sh`.  

*NOTE*: as far as I know, bindgen actually uses clang under the hood, so the options passed as clang-like. Whereas
building C code for the MCU itself will actually be done with `arm-none-eabi-gcc`.  

*NOTE*: The STM32HAL is coded in a way that the line/family/subfamily of MCU parts is selected with a compile-time
macro. Here, `STM32L475xxx`. This crate would have to be edited to change the chip target.  
In the future, it may be possible to provide multiple chip targets as crate-level "features".

A `wrapper.h` is provided in the root of the crate, per standard practice for bindgen usage.

### build.rs

The `build.rs` will build all the associated C code via the `cc` crate.

As with the bindgen bindings, this compilation requires an MCU-specific preprocessor macro to specialize the different 
supported features. The value in `build.rs` must match the value passed to `bindgen`!

Also note: since `arm-none-eabi-gcc` is the compiler used, the flags are now gcc-like, rather than clang-like.

### extra.c/.h

Initial attempts at making this workflow come together prompted me to put a few C wrapper functions into an `extra.c`
file. Ultimately, I figures that most of these (e.g. `SystemClock_config`, `HAL_MSP_Init` callback) should be
application-level responsibilities, and are handled there. See the associated [example usage]().

# Major Limitations / Known Issues

To change platform-specific values (e.g. HSE frequency) or HAL configuration options, the config file in this crate
would have to be edited, bindgen re-run, and the crate rebuilt.

Opinion: This design has issues and it should be changed by ST. All clock values could easily be replaced with 
getter/setter functions into a `clock_config` module, and resolved at link time. Then the whole library could be 
built as a static lib.

### libc

There is a [known issue]() with the `libc` crate that prevents it from emitting basic types, which are needed 
for bindgen.  
I was only able to work around this [making a modification]() to libc to suit my target.  
The `[dependencies.libc]` already points to my patched branch on github.

### Default

The HAL heavily relies on the declaration of structs, which are then passed to functions.

In the usual C way, these structures are not always fully initialized if it is known or expected that the downstream
code can handle this safely. Yes, this is a common pitfal in C. Static analyzers commonly pick up these bug, and clearly Rust has been designed
to be correct-by-construction against this issue.

Here, the bindgen option `--with-derive-default` is used to give the `Default` trait, so structures can be partially 
initialized and then `..Default::default()` used.  
This has *high* potential for pitfalls! Major TODO...

### Enums, macros, etc

As is common for C libraries, the HAL uses a lot of defined values. Some enums are used, but many interger literals 
get emitted.  
The impact of this is currently unknown.

### bingden

#### Macros

The "Low Level" library uses a ton of function-like macros that bindgen totally fails to pick up.

#### static inlines

bindgen has a known limitation of not being able to deal with `static inline` functions.
e.g. `__disable_irq()` is not available.

This is a major limitation, and apparently the only resolution will be feature updates to bindgen.

#### Random hardfaults

Sometimes, on reset or initial flashing, random hardfaults are hit.  
The reason is unknown, but I suspect that the `cortex-m-rt` is not doing quite the same actions for 

# big TODO's

- The STM32 HAL library should be a git submodule
- `build.rs` could invoke bingden?
- Currently, the package is configured for a SINGLE MCU, per definitions needed by the STM32 HAL.
  - Unclear how to work around this ... maybe have crate-level features for each of the possible configs?
- Can we package a known-working example?
  - The example will require a separate `build.rs` to run `cc` on C FFI code. Unclear if that is supported.
- Re-add DSP and NN libraries