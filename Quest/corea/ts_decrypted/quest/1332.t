CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1332;
	title = 133202;

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
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 1030;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 834;
				iprob1 = "1.000000";
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 133209;
				ctype = 1;
				idx = 6412102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 133208;
				gtype = 1;
				area = 133201;
				goal = 133204;
				grade = 132203;
				rwd = 100;
				sort = 133205;
				stype = 2;
				taid = 1;
				title = 133202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 2;
				idx0 = 834;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1030;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 133208;
			gtype = 1;
			oklnk = 2;
			area = 133201;
			goal = 133204;
			sort = 133205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 133202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 133214;
			nextlnk = 101;
			rwdtbl = 133201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2805101;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 1030;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 834;
			}
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
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 133207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6412102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1331;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 133207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx1 = 1030;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 834;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
	}
}
