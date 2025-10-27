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

### High-level Overview

Our game will be utilizing the **Model-View-Controller (MVC)** design pattern for the user
interface.

- **View**: the UI that is visible to the player
- **Controller**: retrieves data from the model and broadcasts it to the view
- **Model**: the code of our game

Note that this design pattern consists of one way dependencies as follows:

	View -> Controller -> Model

So, the controller doesn't depend on the view, which means the view can easily be swapped
out with another view without needing to modify anything in the controller. Likewise,
the model doesn't depend on the controller, meaning the controller can be swapped out without
needing to modify the model.


### Delegates

Our widgets access attributes such as health and mana through a controller class (not
to be confused with the Unreal Player Controller class). This is achieved through
**delegates** created on the controller class.

The base c++ class for which all our widget blueprints are based on is `UAuraUserWidget`.
Any widgets that derive from this class will bind/subscribe to the delegates created
in the controller class. For example, `WBP_HealthGlobe` binds to the `OnHealthChanged` and
`OnMaxHealthChanged` delegates to update the health percentage bar.

We have a c++ class called `UAuraWidgetController` which will act as the base class
for all controllers. This base class has four important fields for accessing the *model*.

- Player Controller
- Player State
- AbilitySystemComponent
- AttributeSet

These are initialized from the player character class `AAuraCharacter`.

The controller that is responsible for retrieving attributes from our *model*
will be the `UOverlayWidgetController` class. It does so by accessing the `AttributeSet`
from our `PlayerState` class.

The `AAuraHUD` is a HUD class that we will use to centralize HUD-related activity. This class
contains fields for a `UOverlayWidgetController` and `UAuraUserWidget`. It is reponsible
for creating the one-way controller dependency and initializing the game overlay
(e.g. initializing the health and mana bars to their default attribute values).
