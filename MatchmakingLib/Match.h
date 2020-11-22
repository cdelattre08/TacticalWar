#pragma once
#include <string>
#include <vector>
#include "Player.h"

namespace tw
{
	enum MatchStatus
	{
		NOT_STARTED,
		STARTED,
		FINISHED
	};

	class Match;
	class MatchEventListener
	{
	public:
		virtual void onMatchStatusChanged(Match * match, MatchStatus oldStatus, MatchStatus newStatus) = 0;
	};

	class Match
	{
	private:
		static int matchId;

		int id;
		std::string name;
		std::vector<Player*> team1;
		//Player * team1PlayerTakeInit;
		std::vector<Player*> team2;
		//Player * team2PlayerTakeInit;

		MatchStatus status;
		int winnerTeam;

		void * battlePayload;

		std::vector<MatchEventListener*> listeners;

		bool playerIsInTeam(Player * p, std::vector<Player*> & team)
		{
			return std::find(team.begin(), team.end(), p) != team.end();
		}

		void notifyStatusChanged(MatchStatus oldStatus, MatchStatus newStatus)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onMatchStatusChanged(this, oldStatus, newStatus);
			}
		}

		std::string serializeTeam(std::vector<Player*> & team, char separatorPlayer, char separatorInfo)
		{
			std::string result;

			for (int i = 0; i < team.size(); i++)
			{
				Player * p = team[i];
				if (i != 0)
					result += separatorPlayer;

				result += std::to_string(p->getTeamNumber()) + separatorInfo;
				result += p->getPseudo() + separatorInfo;
				result += std::to_string(p->getHasJoinBattle() ? 1 : 0);
			}

			return result;
		}

	public:
		Match(std::string name)
		{
			this->id = matchId++;
			this->name = name;
			status = MatchStatus::NOT_STARTED;
			winnerTeam = 0;
			battlePayload = NULL;
		}

		int getId()
		{
			return id;
		}

		void setTeam1Players(Player * p1, Player * p2)
		{
			team1.clear();
			team1.push_back(p1);
			team1.push_back(p2);
		}

		void setTeam2Players(Player * p1, Player * p2)
		{
			team2.clear();
			team2.push_back(p1);
			team2.push_back(p2);
		}


		std::vector<Player*> & getTeam1() {
			return team1;
		}

		std::vector<Player*> & getTeam2() {
			return team2;
		}

		

		bool playerIsInTeam1(Player * p)
		{
			return playerIsInTeam(p, team1);
		}

		bool playerIsInTeam2(Player * p)
		{
			return playerIsInTeam(p, team2);
		}

		bool playerIsInThisMatch(Player * p)
		{
			return playerIsInTeam1(p) || playerIsInTeam2(p);
		}

		MatchStatus getStatus()
		{
			return status;
		}

		std::vector<Player*> * getWinnerTeam()
		{
			if (status == MatchStatus::FINISHED)
			{
				if (winnerTeam == 1)
				{
					return &team1;
				}
				else
				{
					return &team2;
				}
			}

			return NULL;
		}

		void * getBattlePayload()
		{
			return battlePayload;
		}

		void setBattlePayload(void * obj)
		{
			battlePayload = obj;
		}

		void setMatchStatus(MatchStatus status)
		{
			MatchStatus oldStatus = this->status;
			this->status = status;
			notifyStatusChanged(oldStatus, status);
		}

		void addEventListener(MatchEventListener * l)
		{
			listeners.push_back(l);
		}

		void removeEventListener(MatchEventListener * l)
		{
			std::vector<MatchEventListener*>::iterator it = std::find(listeners.begin(), listeners.end(), l);

			if (it != listeners.end())
			{
				listeners.erase(it);
			}
		}

		std::string serialize()
		{
			std::string result = "";
			result = std::to_string(id) + "," + name + "," + std::to_string((int)status) + "," + std::to_string(winnerTeam) + ",";
			result += serializeTeam(team1, '|', '^') + ",";
			result += serializeTeam(team2, '|', '^');
			
			return result;
		}
	};
}