#pragma once

#include "Session.h"

namespace Tetris
{

	class SingleSession : public Session
	{
	public:

		SingleSession(Game& game);

		void update() override;
		void render() override;



	};

} //Tetris