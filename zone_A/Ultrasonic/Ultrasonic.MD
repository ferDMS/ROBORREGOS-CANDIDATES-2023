# Ultrasonic

## Research

It is a sensor that can emit ultrasonic sound waves and receive them back. By using basic physics, one can calculate the distance to a surface based on the time it took for the ultrasonic wave to come back after being emitted. The basic formula for the movement of the waves through air is represented by Uniform Rectilinear Motion 

$$\begin{equation}
v = \frac{d}{t_1}
\end{equation}$$

, where $v$ is the velocity of the wave, $d$ the distance to the surface, and $t$ the time it takes the sensor to receive the wave after bouncing from the surface. $t$ can be obtained as half the time it takes to go from the emitter to the surface, and from the surface to the receiver as $t=\frac{t_t}{2}$. Because $v$ is simply the speed of sound, a known value, by obtaining the $t$, a calculation can be performed to estimate $d$. 

$$v = 0.034\ \mu s \\[10pt]$$

$$
\begin{equation}
d = \frac{0.034t}{2}
\end{equation}
$$


