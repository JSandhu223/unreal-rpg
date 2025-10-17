# Top-down RPG

## Gameplay Ability System

### High-level Overview

This game is developed with Unreal Engine 5.6 and utilizes the 
**Gameplay Ability System (GAS)**. GAS consists of these main parts:

1. **Ability System Component** - component that can be added to an actor.
2. **Attribute Set** - stores information about attributes such as damage, health,
exp, etc.
3. **Gameplay Ability** - classes that encapsulate the functionality of actions a
character can perform (e.g. attacking, casting special moves, etc.)
4. **Ability Task** - these are tasks/jobs that are run asynchronously by
*Gameplay Abilities*.
5. **Gameplay Effect** - these are capable of a handful of things related to modifying
*attributes*.
6. **Gameplay Queues** - handle cosmetic effects such as particle systems and sounds.
7. **Gameplay Tags** - although not exclusive to GAS, they are used extensively with
GAS due to their versatile and hierarchical nature.

### Ability Actor Info

An Ability System Component (ASC) has two variables:

- **Owner Actor**: the class that owns the ability system component.
- **Avatar Actor**: the representation in the world associated with the ability system component

In the case of our player character, since the Ability System Component exists
on the player state class, we have

- Owner Actor = player state
- Avatar Actor = character

Ability actor info is set by calling:

`UAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)`

Note that initialization must be done after posession of the pawn 
(i.e. after the controller has been set for the pawn).
