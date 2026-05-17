# Test Cases

The "tests" in this project are the examples from `examples/` — each example serves as both a demonstration and a compile-time or runtime validation of the bmt library. There are no formal test frameworks.

## Current test files

- `examples/01-clock-tree/Validate.F103.h` — Compile-time `static_assert` GPIO register validation for STM32F103xB
- `examples/01-clock-tree/Validate.G431.h` — Compile-time `static_assert` GPIO register validation for STM32G431xx
- `examples/01-clock-tree/Validate.L432.h` — Compile-time `static_assert` GPIO register validation for STM32L432xx

## Init() → Setup() migration

The bmt library deprecates `Init()` on Timer and DMA types in favor of `Setup()`. Under the `Clocks::Enabler` design (see `bmt/BMT_RCC_ENABLER_DESIGN.md`), each peripheral's clock should be managed centrally and `Setup()` should only configure registers.

### Deprecated Init() methods (with compiler warnings)

**All three platforms:**

| Platform | Timer `Any::Init()` | Timer `AnyOutputChannel::Init()` | DMA `AnyChannel::Init()` | GPIO `AnyPortSetup::Init()` |
|----------|:---:|:---:|:---:|:---:|
| **f1xx** | ✅ deprecated | ✅ (via TimType) | ✅ deprecated | ✅ deprecated |
| **g4xx** | ✅ deprecated | ✅ (via TimType) | ✅ deprecated | ❌ not yet |
| **l4xx** | ✅ deprecated | ✅ (via TimType) | ✅ deprecated | ❌ not yet |

Message on Timer: `"Use platform PeripheralEnabler at boot, then call Setup() directly"`  
Message on DMA: `"Add this DMA channel to platform PeripheralEnabler, then call Setup()"`

### Calls that remain as Init() (not deprecated)

| Call | Reason |
|------|--------|
| `System::Init()` | Global RCC reset — no Setup() alternative |
| `SysClk::Init()` | Clock tree setup — chains through clock source init |
| `Gpio::AnyPortSetup::Init()` | Convenience wrapper; EnableClock() is deprecated on F1 but not yet on g4xx/l4xx |
| `Timer::SysTickCounter::Init()` | Core peripheral, no RCC enable needed; no Setup() alternative |

### Migration completed in examples (2026-05-16)

| Example | Changes |
|---------|---------|
| 04-timer-delay | `Delay::Init()` → `Setup()`, `FiveMs::Init()` → `Setup()` |
| 05-pwm | `LEDR::Init()` → `Setup()` (all three channels now use `Setup()`) |
| 06-dma-pwm | `PwmOut::Init()` → `Setup()`, `Updater::Init()` → `Setup()`, `TheDma::Init()` → `Setup()` |

### Remaining work

- g4xx and l4xx `Init()` methods still use direct RCC register writes (massive switch blocks) rather than `Clocks::Enabler<T>::Init()`. They need integration into the `RccEnabler` framework (adding `RccTrait_` to each peripheral).
- No `PeripheralEnabler` type alias is defined in any example's hal files yet.
- g4xx and l4xx GPIO `AnyPortSetup::Init()` and EXTI `Enable()` are not yet deprecated.
