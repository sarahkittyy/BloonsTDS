#include "Bloons/Wave.hpp"

namespace Bloons
{

Wave::Wave()
{
	mStarted	  = false;
	mCurrentGroup = 0;
	mDone		  = false;
}

void Wave::addGroup(Wave::BloonGroup b)
{
	mGroups.push_back(b);
}

void Wave::setBloonCallback(std::function<void(Bloon&)> sendBloon)
{
	mSendBloon = sendBloon;
}

void Wave::start()
{
	if (mStarted)   //Ignore if already started
	{
		return;
	}
	if (mGroups.size() == 0)   //Extra error checking
	{
		throw std::out_of_range("No bloon groups specified for wave!");
	}
	mStarted	  = true;
	mCurrentGroup = 0;
	mSubTimer	 = 0;
	mDone		  = false;
	nextGroup();
}

bool Wave::isStarted()
{
	return mStarted;
}

bool Wave::isDone()
{
	return mDone;
}

void Wave::stop()
{
	mStarted = false;
	mDone	= true;
	mActiveGroups.clear();
}

void Wave::update()
{
	if (!mStarted || mDone)
	{
		return;
	}

	//Assert there are still active groups. If not, then we're done.
	if (mActiveGroups.empty())
	{
		mDone = true;
		return;
	}
	//We can send another wave if the top wave's duration is over.
	else if (mSubTimer > mActiveGroups.back().group->dur)
	{
		if (mCurrentGroup < mGroups.size())
		{
			mSubTimer = 0;
			nextGroup();
		}
		else
		{
			mDone = true;
			return;
		}
	}

	//Update all existing active waves.
	for (auto& i : mActiveGroups)
	{
		//If they're ready to send another bloon, send one.
		if (i.timer >= i.group->spacing)
		{
			i.timer = 0;

			mSendBloon(i.group->bloon);

			i.index++;
		}

		//Increment their timers.
		i.timer++;
	}

	//Check if any subwaves need to be deleted.
	for (size_t i = 0; i < mActiveGroups.size();)
	{
		//For iterating safety.
		bool popped = false;

		SubWave* sub = &mActiveGroups[i];

		//If their bloon index is over their ct..
		if (sub->index >= sub->group->ct)
		{
			//..Delete it.
			mActiveGroups.erase(mActiveGroups.begin() + i);
			popped = true;
		}

		if (!popped)
		{
			i++;
		}
	}

	//Increment the subwave timer.
	mSubTimer++;
}

void Wave::nextGroup()
{
	// clang-format off
	mActiveGroups.push_back({
		.group = &mGroups[mCurrentGroup],
		.timer = 0,
		.index = 0
	});
	// clang-format on
	mCurrentGroup++;
}

}