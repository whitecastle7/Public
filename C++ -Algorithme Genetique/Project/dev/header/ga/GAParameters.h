#pragma once
#ifndef GA_PARAMETERS_H
#define GA_PARAMETERS_H


#include "GAEngine.h"
class SelectionStrategy;
class CrossoverStrategy;
class MutationStrategy;
class Solution;


class GAParameters
{
public:
    GAParameters();
    GAParameters(GAParameters const &) = delete;
    GAParameters(GAParameters &&) = delete;
    GAParameters operator=(GAParameters const &) = delete;
    GAParameters operator=(GAParameters &&) = delete;
    ~GAParameters();

    bool isValid() const;

    size_t populationSize() const;
    size_t ellitismSize() const;
    size_t concurrentPopulationCount();
    size_t maximumGenerationCount() const;

    SelectionStrategy & selectionStrategy();
    CrossoverStrategy & crossoverStrategy();
    MutationStrategy & mutationStrategy();
    Solution const & solutionSample() const;

    void setPopulationSize(size_t size);
    void setEllitismSize(size_t size);
    void setConcurrentPopulationCount(size_t count);
    void setMaximumGenerationCount(size_t count);

    void setSelectionStrategy(SelectionStrategy * strategy);
    void setCrossoverStrategy(CrossoverStrategy * strategy);
    void setMutationStrategy(MutationStrategy * strategy);
    void setSolutionSample(Solution * solution);

    void clearAll();
    void setToDefault();

private:
    size_t mPopulationSize{};
    size_t mEllitismSize{};
    size_t mConcurrentPopulationCount{};
    size_t mMaximumGenerationCount{};

    Solution * mSolutionSample{};
    SelectionStrategy * mSelectionStrategy{};
    CrossoverStrategy * mCrossoverStrategy{};
    MutationStrategy * mMutationStrategy{};
};


#endif // GA_PARAMETERS_H