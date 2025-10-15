


#include "Player/AuraPlayerState.h"


AAuraPlayerState::AAuraPlayerState()
{
	// The net update frequency is the max number of tries per second an actor is going to try to send an update.
	// This is how often the server will try to update clients.
	// As changes occur on the server for the player state, the server will be sending updates out to all clients
	// so they can sync up with the server version (e.g. any variables that need to be replicated).
	// The server will try to meet the net update frequency value if it can.
	this->NetUpdateFrequency = 100.0f;
}
