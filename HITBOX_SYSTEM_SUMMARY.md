# Hitbox/Hurtbox System Implementation

## Overview

HAMOOPI features a professional-grade collision system with multiple collision box types for accurate fighting game mechanics.

## Collision Box Types

### 1. Hurtbox (Vulnerable Area)
- **Color**: Green (in debug mode)
- **Purpose**: Defines where a player can be hit
- **Normal Size**: 24x38 pixels, centered on player
- **Blocking Size**: 20x35 pixels (smaller, rewards defensive play)
- **Function**: `get_hurtbox(Player* p)`
- **Used For**:
  - Detecting when attacks hit the player
  - Projectile collision detection
  - Taking damage calculations

### 2. Hitbox (Attack Area)
- **Color**: Red (in debug mode)
- **Purpose**: Defines the attacking area during punch animations
- **Size**: 35x20 pixels, extended in front of player
- **Active Frames**: Frames 2-6 of attack animation (5 frames)
- **Function**: `get_hitbox(Player* p)`
- **Used For**:
  - Checking if attack connects with opponent's hurtbox
  - Dealing damage when overlapping with hurtbox
  - Frame-accurate attack timing

### 3. Body Collision Box (Physical Presence)
- **Color**: Yellow (in debug mode)
- **Purpose**: Prevents players from walking through each other
- **Size**: 30x40 pixels, centered on player
- **Function**: `get_body_box(Player* p)`
- **Used For**:
  - Pushing players apart when they get too close
  - Maintaining physical spacing during movement
  - Preventing overlap during all game states

### 4. Clash/Priority Box (Attack Interaction)
- **Color**: Orange (in debug mode)
- **Purpose**: Detects when two attacks meet
- **Size**: 45x25 pixels, extended in front during attack
- **Active Frames**: Frames 1-7 of attack animation (7 frames, includes startup)
- **Function**: `get_clash_box(Player* p)`
- **Used For**:
  - Detecting simultaneous attacks
  - Canceling both attacks when they clash
  - Creating tactical attack timing gameplay
  - Pushing players back on clash

### 5. Projectile Hitbox
- **Color**: Magenta (in debug mode)
- **Purpose**: Fireball/projectile collision area
- **Size**: Varies by projectile type
- **Radius**: 30 pixels for hit detection
- **Stored In**: `Projectile.hitbox` field
- **Used For**:
  - Checking if projectile hits opponent's hurtbox
  - Dealing projectile damage
  - Destroying projectile on hit

## Collision Detection System

### Box Overlap Function
```cpp
bool boxes_overlap(CollisionBox a, CollisionBox b)
```
- Standard AABB (Axis-Aligned Bounding Box) collision
- Returns true if boxes intersect
- Used for all collision checks

### Collision Resolution Priority

1. **Attack Clashing** (Highest Priority)
   - Checked when both players are attacking (state == 3)
   - If clash boxes overlap → cancel both attacks
   - Push players back with knockback
   - Play clash sound effect

2. **Attack Hits**
   - P1 hitbox vs P2 hurtbox
   - P2 hitbox vs P1 hurtbox
   - Applies damage (5 HP normal, 1 HP blocked)
   - Triggers hit sound effect
   - Applies cooldown to prevent multiple hits

3. **Projectile Hits**
   - Each active projectile checks against opponent's hurtbox
   - Deals damage on collision
   - Destroys projectile after hit
   - Works independently of normal attacks

4. **Body Collision** (Lowest Priority)
   - Always active during gameplay
   - Pushes players apart smoothly
   - Maintains 2-pixel minimum separation

## Debug Visualization

### Toggle Debug Boxes
- **Control**: Press SELECT button (mapped to '1' key for P1) during fight
- **State**: Persists across rounds
- **Purpose**: Visualize collision boxes for development/testing

### Debug Display
When enabled, shows:
- Green boxes = Hurtboxes (where you can be hit)
- Red boxes = Hitboxes (where your attack hits)
- Yellow boxes = Body collision (physical presence)
- Orange boxes = Clash boxes (attack collision)
- Magenta boxes = Projectile hitboxes

## Gameplay Impact

### Blocking Mechanics
- Hurtbox shrinks when blocking (20x35 vs 24x38)
- Smaller target makes blocking more rewarding
- Still takes 1 HP chip damage
- Visual shield indicator shows block state

### Attack Timing
- Hitbox active for 5 frames (2-6)
- Clash box active for 7 frames (1-7, includes startup)
- Frame-perfect timing matters
- Can clash attacks during startup frames

### Spacing Control
- Body collision prevents players from occupying same space
- Smooth push-apart system (2 pixels per frame)
- Maintains proper fighting game spacing
- No overlapping sprites

### Attack Clashing
- When two attacks meet (clash boxes overlap)
- Both attacks cancel
- Players pushed back (creates space)
- Tactical decision: attack vs wait for opponent
- Risk/reward for simultaneous attacks

## Technical Implementation

### CollisionBox Structure
```cpp
typedef struct {
    float x, y;     // World position (absolute coordinates)
    float w, h;     // Width and height
} CollisionBox;
```

### Attack Frame Tracking
- `Player.attack_frame` tracks current attack animation frame
- Increments each frame during attack (state == 3)
- Determines when hitbox and clash box are active
- Reset to 0 when attack completes

### Collision Check Order
1. Check attack clashing first (both attacking)
2. Check P1 attack hits P2
3. Check P2 attack hits P1
4. Check projectile collisions
5. Check body collision (push apart)

## Balance Considerations

### Hitbox Timing
- Active for 5 frames @ 60 FPS = 0.083 seconds
- Short duration rewards precise timing
- Prevents spamming attacks

### Clash Box
- Active 2 frames longer than hitbox (startup + active)
- Can clash during attack startup
- Creates tactical depth

### Hurtbox Sizes
- Normal: 24x38 pixels
- Blocking: 20x35 pixels
- 16.7% smaller width when blocking
- 7.9% smaller height when blocking

### Body Collision
- Larger than hurtbox (30x40 vs 24x38)
- Ensures players can't phase through
- Smooth push system prevents jittering

### Projectile Collision
- 30x30 pixel square hitbox for hit detection
- PROJECTILE_HIT_RADIUS constant defines collision range
- Destroyed on hit (can't hit both players)

## Future Enhancements

Possible additions:
- **Low/High/Mid attacks** with different hurtbox checks
- **Crouching** with altered hurtbox
- **Air attacks** with aerial hitboxes
- **Throw boxes** for grab mechanics
- **Counter hit** system with extended hitstun
- **Pushback on block** using body collision

## Performance

- All box calculations done in CPU
- Simple AABB collision (very fast)
- O(1) collision checks (fixed player count)
- No performance impact at 60 FPS
- Debug visualization minimal overhead

## Code References

- **Collision Functions**: Lines 58-164 in hamoopi_core.cpp
- **Attack Logic**: Lines 1232-1460 in hamoopi_core.cpp
- **Debug Drawing**: Lines 169-176, 676-679, 1509-1512
- **Projectile System**: Lines 43-51, 457-497

## Summary

The hitbox/hurtbox system provides:
✅ Professional fighting game collision detection
✅ Frame-accurate attack timing
✅ Attack clashing mechanics
✅ Blocking rewards (smaller hurtbox)
✅ Body collision for spacing
✅ Projectile collision system
✅ Debug visualization tools
✅ Balanced gameplay mechanics

All collision systems are fully implemented, tested, and production-ready!
