# tortin_samples

This public repository contains small examples of the core simulator Tortin.

The gui folder shows how the geometry of the core can be setup in Tortin.

And the interpolation folder contains the routine used for interpolations of the cross sections. They are interpolated by multi-dimensional linear or cubic functions. 
The routine is very well vectorized; the speed up for 32 bit float numbers on the 256 bit Intel CPU is about 7.5.
