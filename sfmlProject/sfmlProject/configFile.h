/*
This namespace are responsible for settings that can be changed by the user
*/
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

namespace generalSettings
{
	int const DEFAULT_WINDOW_WIDTH = 600;
	int const DEFAULT_WINDOW_HEIGHT = 400;

	//tree
	int const IMAGE_WIDTH = 736;
	int const IMAGE_HEIGHT = 460;

	//ocean
	//int const IMAGE_WIDTH = 507;
	//int const IMAGE_HEIGHT = 285;

	//tower
	//int const IMAGE_WIDTH = 1428;
	//int const IMAGE_HEIGHT = 968;

}

namespace coreSettings
{
	int const NR_OF_STATES = 4;
}

#endif


