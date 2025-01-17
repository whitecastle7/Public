
#include "Analyse_Statistique.h"


Analyse_Statistique::Analyse_Statistique()
	: l{ 0 }, h{ 0 }, pivot{ 0 }, temp{ 0 }, mI{ 0 }, mFound{ false }, mRepeat{ 0 },
	mMin{ 0 },
	mMax{ 0 },
	mSpan{ 0 },
	mMedian{ 0 },
	mMode{ 0 },
	mCount{ 0 },
	mSum{ 0 },
	mAverage{ 0 },
	mVariance{ 0 },
	mDeviation{ 0 }
{
}

std::string const & Analyse_Statistique::process_description()
{
	static std::string processDescrp ("processus description");
	return processDescrp;
}

std::string const & Analyse_Statistique::implementation_description()
{
	static std::string impDescrp ("implementation description");
	return impDescrp;
}

std::string const & Analyse_Statistique::implementation_id()
{
	static std::string impID ("0");
	return impID;
}

std::string const & Analyse_Statistique::author_name()
{
	static std::string name ("Roy Vincent");
	return name;
}

std::string const & Analyse_Statistique::author_id()
{
	static std::string id ("0845259");
	return id;
}



void Analyse_Statistique::do_process(data const & d)
{
	if (!d.empty())
	{
		mSorted = d;
		mCount = mSorted.size();

		if (mCount > 1)
		{
			quickSort(0, mCount - 1);
		}

		mMin = mSorted[0];
		mMax = mSorted[mCount - 1];
		mSpan = mMax - mMin;
		median();
		mode(d);
		sum();
		mAverage = mSum / mCount;
		variance();
		mDeviation = mVariance.sqrt();

		_statistical_metric.set(mMin, mMax, mSpan, mMedian, mMode, mCount, mSum, mAverage, mVariance, mDeviation);
	}
	else
	{
		_statistical_metric.set_to_zero_data();
	}
}

void Analyse_Statistique::quickSort(int low, int high)
{
	l = low;
	h = high;
	pivot = mSorted[(l + h) / 2];

	while (l <= h)
	{
		while (mSorted[l] < pivot)
		{
			l++;
		}
		while (mSorted[h] > pivot)
		{
			h--;
		}
		if (l <= h)
		{
			temp = mSorted[l];
			mSorted[l] = mSorted[h];
			mSorted[h] = temp;
			l++;
			h--;
		}
	}
	if (h > low)
	{
		quickSort(low, h);
	}
	if (l < high)
	{
		quickSort(l, high);
	}
}


void Analyse_Statistique::median()
{
	if (mCount % 2 == 0)
	{
		mMedian = (mSorted[mCount / 2 - 1] + mSorted[mCount / 2]) / real(2);
	}
	else
	{
		mMedian = mSorted[mCount / 2];
	}
}

void Analyse_Statistique::mode(data const & d)
{
	mModeList.clear();
	mRepeat = 0;

	// for (auto it{d.begin(); it != d.end(); ++it}	// *it
	for (real const & r : d)
	{
		mFound = false;
		mI = r.round();
		for (std::pair<integer, int> & p1 : mModeList)
		{
			if (mI == p1.first)
			{
				mFound = true;
				++p1.second;
				break;
			}
		}
		if (!mFound)
		{
			mModeList.emplace_back(mI, 1);
		}
	}

	for (std::pair<integer, int> const & p2 : mModeList)
	{
		if (p2.second > mRepeat)
		{
			mRepeat = p2.second;
			mMode = p2.first;
		}
	}
}

void Analyse_Statistique::sum()
{
	mSum = 0;
	for (real const & r : mSorted)
	{
		mSum += r;
	}
}

void Analyse_Statistique::variance()
{
	mVariance = 0;
	for (real const & r : mSorted)
	{
		mVariance += (r - mAverage).square();
	}
	mVariance = mVariance / mCount;
}
