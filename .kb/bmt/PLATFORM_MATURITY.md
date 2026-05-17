# Platform Maturity

The **F1xx** platform is the most mature reference implementation in the bmt library. Newer platforms (g4xx, l4xx) are less mature and sometimes drifted from F1xx conventions — e.g., renaming methods instead of keeping them consistent.

**When there's a naming conflict between platforms, update the less mature platform to match F1xx**, not the other way around.

Example: `AnyPinGroup::Setup()` is the F1xx naming. g4xx/l4xx renamed it to `Enable()`. The fix should be to add `Setup()` as an alias on g4xx/l4xx, not add `Enable()` to F1xx.
