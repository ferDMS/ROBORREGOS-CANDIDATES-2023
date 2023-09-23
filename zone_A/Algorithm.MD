# Algorithm for Zone A

## General picture

Use the 3 ultrasonic devices located on the right, left and front of the robot to search for possible square movements. Because the ultrasonic's range is $2\ cm$ to $400\ cm$, if at any time one ultrasonic is too close to a wall and can't work properly because of this, then we can just recenter the robot. It should not be a problem to use ultrasonics because the movements are octogonal, thus staying inside the cone working angle of $30\degree$. The ultrasonics are placed at less than $15\ cm$ to the floor, so their pulses can reflect on the outer walls as well.
