#pragma once

#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Bloons/Bloon.hpp"

namespace Bloons
{

/**
 * @brief Defines a single wave of bloons, including timings and count.
 * 
 * @remarks Timers are 1/60th of a second.
 * 
 */
class Wave
{
public:
	/**
	 * @brief A grouping of bloons, categorized by a spacing between
	 * each one, a count of bloons and a duration until the next wave.
	 * 
	 */
	struct BloonGroup
	{
		Bloon bloon;
		time_t spacing;
		size_t ct;
		time_t dur;
	};

private:
	/**
	 * @brief A "SubWave" is a bloon group with a timer and index padded on.
	 * The index is how many bloons have been sent so far,
	 * while the timer is storing the time between each bloon send.
	 * 
	 */
	struct SubWave
	{
		BloonGroup* group;
		time_t timer;
		size_t index;
	};

public:
	/**
	 * @brief Construct a new Wave
	 * 
	 */
	Wave();

	/**
	 * @brief Add a bloon group to the subwaves in this wave.
	 * 
	 * @param b The group to add.
	 */
	void addGroup(BloonGroup b);

	/**
	 * @brief Set the function callback when a bloon needs to be sent.
	 * 
	 * @param sendBloon A function that takes in a reference
	 * to a bloon.
	 */
	void setBloonCallback(std::function<void(Bloon&)> sendBloon);

	/**
	 * @brief Start the wave.
	 * 
	 */
	void start();

	/**
	 * @brief Stop the wave.
	 * 
	 */
	void stop();

	/**
	 * @brief Update the wave. Call once per frame, while running.
	 * Calling while stopped will have no effect.
	 * 
	 */
	void update();

private:
	/**
	 * @brief Whether or not the wave is started.
	 * 
	 */
	bool mStarted;

	/**
	 * @brief The constant groups of bloons to send over the course of the wave.
	 * 
	 */
	std::vector<BloonGroup> mGroups;

	/**
	 * @brief The index of the next group to send.
	 * 
	 */
	size_t mCurrentGroup;

	/**
	 * @brief The active, updating groups.
	 * Groups from mGroups are put here when
	 * nextGroup() is called.
	 * 
	 */
	std::vector<SubWave> mActiveGroups;

	/**
	 * @brief The callback whenever a bloon is sent.
	 * 
	 */
	std::function<void(Bloon&)> mSendBloon;

	/**
	 * @brief The subwave timer, counts frames until the current
	 * group's total duration is over, to which nextGroup() is called.
	 * 
	 */
	time_t mSubTimer;

	/**
	 * @brief Adds the next group from mGroups into the active group
	 * pool, incrementing the index.
	 * 
	 */
	void nextGroup();
};

}