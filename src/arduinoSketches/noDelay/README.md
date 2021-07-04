A series of examples which avoid using the `delay()` function

This is important since while 
`delay()` 
is running, no code is running; in particular, 
no sensors are read, thus making the system non-responsive.

All examples in this group are based on the principles of the 
`Blink Without Delay`
built-in example (file -> examples -> digital -> Blink Without Delay)
