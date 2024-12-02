# Sample Test Assignment

## Assignment description

Create a new Unreal Engine 5.4 project.

Features:
- Ranged weapon shooting projectiles (you may use the first person template for this)
- 4 ammunition types: Regular (deals damage), Fire (deals fire damage and applies
on fire effect to the target), Water (puts out flames and cancels on fire effects),
Healing (heals the target). You don’t need to add particle effects, changing colors of
assets is enough.
- On fire effect: deals fire damage periodically to the target, expires after some time by
itself or by water.
- Damage system with multiple types and resistances to each one
- Health displaying over actors (basic UI or debug draws are enough)

## Solution Details

### Damage Types and ammunition
In completing the assignment I focused the most on the extensibility aspect of it - with designers in mind. The system allows for easy and seamless addition of new damage types and new damage resistances that can fill a distinct gameplay niche. Each new Damage Type can operate independantly from others or have interactions with them - everything is defined in a matter of few clicks. In order to demonstrate that, I added another damage type - Poison - following the design rules:
- After a short delay (onset) rapidly depletes health by small values (to differentiate from Fire effect that depletes health every second by larger values, without the initial delay)
- Can be stopped by Healing projectile (similarly to how Water stops Fire effect)

Adding a new, fully funcional damage type (or damage cancellation type) takes about a 2 minutes, then it works seamlessly. The list of steps:
- Adding an Enum value in DamageEnums.h to represent the new damage type
- Handling input for it - Creating corresponding InputAction and adding it to the Mapping Context IMC_DamageTypes
- Creating a projectile asset for the new damage type
- Mapping the projectile to the new DamageType Enum in DA_DamageSettings->ProjectilesForDamageTypes
- Mapping the input to the new DamageType Enum in DA_DamageSettings->DamageTypeInputs

### Damage Resistances and targets
In order to demonstrate the damage interactions, target cubes have been placed on the scene. They have a health display hovering above and follow the set of rules:
- White cube - basic target. No resistances / modifications.
- Red cube - Fire-vulnerable cube. Severely reduced Basic & Poison damage, regular Fire damage.
- Green cube - Poison-vulnerable cube. Severely reduced Basic & Fire damage, double Poison damage.
- Black cube - "Undead rules" cube. Reduced Basic & Fire damage. Healing damages the cube, Poison heals the cube.

Adding a new type of target is even easier than adding a new type of damage - all it takes is creating a child BP from BP_BaseTarget and editing the values of DamageResistane within its DamageSystemComponent.

### Project organization
I've made sure to keep my own code separate from the FPP template code, so there's no need to scour that code for anything added/modified by me. The only changes there was making about 2 methods virtual in order to override them in children classes. The entirety of the C++ code created for this assignment is located in the Public/Private folders of the solution (as opposed to the Unreal starter code that's just loose in the main Majewski_TestTask project folder). As for Editor stuff and assets, all of those created by me are located in the TestTaskAssets folder - everything else is the starter content and has not been subject to any changes.

### Controls
After picking up the gun, use numeric keys 1 to 5 to switch between damage types:
- 1 - Basic Damage - white projectile
- 2 - Fire Damage - red projectile
- 3 - Water Damage - blue projectile
- 4 - Healing Damage - green projectile
- 5 - Poison Damage - toxic-green projectile

The rest is as in the regular FPP project - WSAD to walk, space to jump, LMB to shoot
