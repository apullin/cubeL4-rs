bindgen wrapper.h -o src/bindings.rs \
  --use-core --raw-line "extern crate core;" \
  --ctypes-prefix=libc \
  --builtins \
  --with-derive-default \
  -- \
  -I. -I./Drivers/STM32L4xx_HAL_Driver/Inc/ \
  -I./Drivers/CMSIS/Device/ST/STM32L4xx/Include/ \
  -I./Drivers/CMSIS/Include \
  -I./src \
  -DSTM32L475xx -DUSE_HAL_DRIVER \
  --target=thumbv7em-none-eabihf -mthumb -march=armv7em