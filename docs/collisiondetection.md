# Collision detection

## None
`REB_COLLISION_NONE`        

No collision detection, default

## Direct
`REB_COLLISION_DIRECT`      

Brute force collision search, O(N^2), checks for instantaneous overlaps only 

## Line
`REB_COLLISION_LINE`        

This is a brute force collision search and scales as $O(N^2)$.
This algorithm checks for overlapping particles during the last timestep (not just at the end).
It assumes particles travelled along straight lines during the timestep.

## Tree
`REB_COLLISION_TREE`        

This method uses the oct tree to check for overlapping particles at the end of the timestep. It scales as $O(N log(N))$.

## Linetree
`REB_COLLISION_LINETREE`    

This method uses the oct tree and scales as $O(N log(N))$.  
In contrast to `REB_COLLISION_TREE`, this algorithm checks for overlapping trajectories, not only overlapping particles.


