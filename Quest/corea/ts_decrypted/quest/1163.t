CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1163;
	title = 116302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 116307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3172201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 116314;
			nextlnk = 101;
			rwdtbl = 116301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172201;
			}
			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 116309;
				ctype = 1;
				idx = 3172201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 116308;
				m1fx = "-571.000000";
				m2fz = "2777.000000";
				m1fy = "0.000000";
				sort = 116305;
				m2widx = 1;
				grade = 132203;
				m0fx = "-385.000000";
				m0ttip = 116315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 116302;
				gtype = 2;
				area = 116301;
				goal = 116304;
				m0fz = "2980.000000";
				m0widx = 1;
				m1ttip = 116315;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "3063.000000";
				m2fx = "-834.000000";
				m2ttip = 116315;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 922;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 116308;
			gtype = 2;
			oklnk = 2;
			area = 116301;
			goal = 116304;
			sort = 116305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 116302;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 116307;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 922;
				taid = 1;
				type = 1;
			}
		}
	}
}
