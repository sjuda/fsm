#include "stdafx.h"
#include "map"
#include "vector"
#include "string"
//#include "fstream"
using namespace std;

template <typename StateType, typename InputType, typename OutputType>
class FiniteStateMachine
{
public:
	FiniteStateMachine()
	{
		curstate = NULL;
	}
	FiniteStateMachine& AddState(const StateType& state, const OutputType& output, map<InputType, StateType>&Table)
	{
		States.insert(pair<StateType, pair<OutputType, map<InputType, StateType>>>(state, pair<OutputType, map<InputType, StateType>>(output, Table)));
		return *this;
	}
	void SetState(const StateType& state)
	{
		curstate = state;
	}

	OutputType operator()(const InputType& input)
	{
		for (auto&i : States)
		{
			StateType R;
			bool Has = false;
			for (auto&s : i.second.second)
			{
				if (input == s.first)
				{
					Has = true;
					R = s.second;
				}
			}
			if (Has == true)
				return States.at(R).first;
		}
		throw runtime_error("Error");
	}
	void ChangeOutput(const StateType& state, const OutputType& newOut)
	{
		States.at(state).first = newOut;
	}
	void ChangeAction(const StateType& state, const InputType& input, const StateType& newState)
	{
		States.at(state).first = input;
		curstate = newState;
	}
	map<StateType, pair<OutputType, map<InputType, StateType>>> States;
	StateType curstate;
};
