/**
 * Do not edit below this line!
 */
public Extension:__ext_signals = 
{
	name = "Signals",
	file = "signals.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

/**
 * @brief Called whenever a signal is handled
 *
 * @param signal	Kind of signal
 *
 * @noreturn 
 */
forward OnPlayerSayChat(signal);