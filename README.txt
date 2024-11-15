Gladiator project

I. Architecture

Gladiator (C++ Character class) 
	=> BP_Gladiator (Player pawn)
	=> BP_EnemyGladiator (Enemy pawn)
	
The player controls a BP_Gladiator object controlled by
a PC_Gladiator (parent class: GladiatorController)
with the following inputs mapped:
	- Move 	 : WASD
	- Jump 	 : Space bar
	- Attack : Left mouse button
	
The AI is controlled by an AIC_Gladiator (parent class GladiatorAIController)
along with a single AIDirector placed in the level.

This AI Director recalculates enemy positions and decides which enemy can attack
every second (editable in-editor in AI Director instance)


II. Features implemented (all mandatory features were implemented, no bonuses)

- Camera
	=> Third person
	=> No collision tests against enemies

- Player controller
	=> Player movement (no strafing)
	=> Player attack
	=> Player damage VFX (red material)
	
- Enemy AI controller (Behavior tree/Blackboard)
	=> Chasing player
	=> Maintaining line of sight with player
	=> Attacking player one at a time
	=> Damage VFX and death animation
	
- Game state
	=> Menu appears when all enemies are dead
	=> Menu appears when player dies
	
- HUD
	=> Player health bar in top left corner of screen
	=> Enemy health bars on top of them in 3D world space
	
- Day/Night cycle
	=> Sun moving and sky changing color
	=> Day to night and night to day cycle
	
- Sound
	=> Attack sound effects
	=> Footsteps according to material (see limitations)
	=> Different ambient musics for day and night (relative to sun orientation)
	=> Different jingles when dying or beating all enemies 
	
	
III. Limitations and known bugs

- Sound
	=> I was unable to find the stone material to apply the "Stone" physics material
	and play a different sound when stepping on it. It does not affect gameplay as invisible walls
	stop player from walking on most stone areas anyway

- Collision detection
	=> Collisions with gladiator hammers are a bit weird, due to how far the hammer reaches
	during the attack animation. I tried to reduce the damage window by reducing the 
	AttackNotifyState length and saw a minor improvement.
