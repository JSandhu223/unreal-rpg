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

### Replication

Replication refers to the process of the server sending updates of actor data to clients
periodically. The rate at which the server can send this info is set by
`AActor::NetUpdateFrequency`, which determines the max number of times per second the server
will try to send information. There are three different replication modes which control how
much info is replicated from the server to client.

1. **Full** - gameplay effects are replicated to all clients
2. **Mixed** - gameplay effects are replicated only to the *owning client*, while gameplay
cues and gameplay tags are replicated to all clients
3. **Minimal** - gameplay effects are not replicated, while gameplay cues and gameplay tags
are replicated to all clients

Notice that gameplay cues and gameplay tags are always replicated to all clients, regardless
of which replication mode is selected.

### Ability Actor Info

An Ability System Component (ASC) has two important class variables:

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


### Attributes

An attribute is an object of type `FGameplayAttributeData` and is stored in an attribute set.
Attributes are modified by gameplay effects. They consist of two values:

1. **Base Value** - the permanent value of an attribute
2. **Current Value** - the base value plus any temporary modifications caused by gameplay effects

## Game UI

Our game will be utilizing the **Model-View-Controller (MVC)** design pattern for the user
interface.

- **Model**: the code of our game
- **View**: the UI that is visible to the player
- **Controller**: retrieves data from the model and broadcasts it to the view

Note that this design pattern consists of one way dependencies as follows:

	View -> Controller -> Model

So, the controller doesn't depend on the view, which means the view can easily be swapped
out with another view without needing to modify anything in the controller. Likewise,
the model doesn't depend on the controller, meaning the controller can be swapped out without
needing to modify the model.