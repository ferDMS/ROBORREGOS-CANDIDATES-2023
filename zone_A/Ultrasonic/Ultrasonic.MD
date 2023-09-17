# Ultrasonic *HC-SR04*

## Research

It is a sensor that can emit ultrasonic sound waves and receive them back. By using basic physics, one can calculate the distance to a surface based on the time it took for the ultrasonic wave to come back after being emitted. The basic formula for the movement of the waves through air is represented by Uniform Rectilinear Motion 

$$\begin{equation}
v = \frac{d}{t_s}
\end{equation}
$$

, where $v$ is the velocity of the wave, $d$ the distance to the surface, and $t$ the time it takes the sensor to receive the wave after bouncing from the surface. $t_s$ can be obtained as half the time it takes for the wave to be emitted, bounce, and come back to the receiver, as the velocity of sound is constant. This means that $$t_s=\frac{t}{2}$$ Because $v$ is simply the speed of sound, a known value, by obtaining $t_s$, a calculation can be performed to estimate $d$. 

$$v = 0.034\ \mu s$$

$$d = v\ t_s = \frac{v\ t}{2}$$

$$
\begin{equation}
d = 0.017\ t
\end{equation}
$$


