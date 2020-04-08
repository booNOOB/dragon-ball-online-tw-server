#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <Game\Object\Manager\Fight.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>
//#include <TimerJs.h>

float Player::CalculeSkillDamage(BYTE Skill_Effect_Type[2], double SkillValue[2], float damage)
{
	float newDamage = damage;
	for (int i = 0; i < 2; i++)
	{
		switch ((eSYSTEM_EFFECT_APPLY_TYPE)Skill_Effect_Type[i])
		{
			case SYSTEM_EFFECT_APPLY_TYPE_VALUE:
			{
				newDamage += SkillValue[i];
				sLog.outBasic("Add damage %f", SkillValue[i]);
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_VALUE");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_PERCENT:
			{
				float newPercent = SkillValue[i] * 0.01;
				newDamage += damage * newPercent;
				sLog.outBasic("Add percent %f", SkillValue[i]);
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_PERCENT");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_MAX_LP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_LP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_MAX_EP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_EP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_MAX_RP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_RP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_LP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_LP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_EP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_EP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_RP:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_RP");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_OFFENCE:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_OFFENCE");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_OFFENCE:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_OFFENCE");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_DEFENCE:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_DEFENCE");
				break;
			}
			case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_DEFENCE:
			{
				sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_DEFENCE");
				break;
			}
		}
	}
	sLog.outBasic("NewDamage by skill %f original damage %f", newDamage, damage);
	return newDamage;
}

float Player::GetValueByEffectType(BYTE bySkill_Effect_Type, float skillValue, float value)
{
	float newValue = 0;
	switch ((eSYSTEM_EFFECT_APPLY_TYPE)bySkill_Effect_Type)
	{
		case SYSTEM_EFFECT_APPLY_TYPE_VALUE:
		{
			newValue = skillValue;
			sLog.outBasic("Add value %f", newValue);
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_VALUE");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_PERCENT:
		{
			float newPercent = skillValue * 0.01;
			newValue = value * newPercent;
			sLog.outBasic("Add percent %f add value %f", skillValue, newValue);
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_PERCENT");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_MAX_LP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_LP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_MAX_EP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_EP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_MAX_RP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_MAX_RP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_LP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_LP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_EP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_EP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_RP:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_RP");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_OFFENCE:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_OFFENCE");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_OFFENCE:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_OFFENCE");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_DEFENCE:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_PHYSICAL_DEFENCE");
			break;
		}
		case SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_DEFENCE:
		{
			sLog.outBasic("SYSTEM_EFFECT_APPLY_TYPE_CURRENT_ENERGY_DEFENCE");
			break;
		}
	}
	return newValue;
}

bool Player::SetUnsetBuffEffect(sSKILL_TBLDAT* skillData, int index, bool set)
{
	bool isBuff = false;

	int setUnset = set ? 1 : -1;

	if (set)
	{
		sLog.outBasic("Add buff effect");
	}
	else
	{
		sLog.outBasic("Delete buff effect");
	}

	sSYSTEM_EFFECT_TBLDAT* SystemEffectData = NULL;
	SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(skillData->skill_Effect[index]);

	if (SystemEffectData != NULL)
	{
		/*sLog.outBasic("Skill EffectCode %d Skill value %f skill tblidx %d",
			SystemEffectData->effectCode, skillData->SkillValue[index], skillData->tblidx);*/
		switch (SystemEffectData->effectCode)
		{
			case ACTIVE_SKILL_COOL_TIME_DOWN:
			{
				float skillCoolTime = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.fCoolTimeChangePercent);
				skillCoolTime *= -1;
				skillCoolTime *= setUnset;
				sLog.outBasic("skillCoolTime %f", skillCoolTime);
				GetAttributesManager()->UpdateCoolTimeChangePercent(skillCoolTime, true);
				isBuff = true;
				break;
			}
			case ACTIVE_PHYSICAL_DEFENCE_DOWN:
			{
				if (set)
				{
					GetPcProfile()->avatarAttribute.wBasePhysicalDefence = GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
				}

				int subPhysicalDefence = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBasePhysicalDefence);

				subPhysicalDefence = subPhysicalDefence * -1;

				subPhysicalDefence *= setUnset;

				GetAttributesManager()->UpdatePhysicalDefence(subPhysicalDefence, true);
				sLog.outBasic("physical defense substraction %d", subPhysicalDefence);
				isBuff = true;

				if (!set)
				{
					GetPcProfile()->avatarAttribute.wBasePhysicalDefence = 0;
				}

				break;
			}
			case ACTIVE_ENERGY_DEFENCE_DOWN:
			{
				if (set)
				{
					GetPcProfile()->avatarAttribute.wBaseEnergyDefence = GetPcProfile()->avatarAttribute.wLastEnergyDefence;
				}
				int subEnergyDefence = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBaseEnergyDefence);
				subEnergyDefence = subEnergyDefence * -1;

				subEnergyDefence *= setUnset;

				sLog.outBasic("energy defense substraction %d", subEnergyDefence);
				GetAttributesManager()->UpdateEnergyDefence(subEnergyDefence, true);

				isBuff = true;

				if (!set)
				{
					GetPcProfile()->avatarAttribute.wBaseEnergyDefence = 0;
				}
				break;
			}
			case ACTIVE_ATTACK_RATE_DOWN:
			{
				int attackRate = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBaseAttackRate);
				attackRate *= -1;

				attackRate *= setUnset;
				sLog.outBasic("attackRate %d", attackRate);
				GetAttributesManager()->UpdateHitRate(attackRate, true);
				isBuff = true;
				break;
			}
			case ACTIVE_RP_CHARGE_SPEED://need Handle the effect is here to try do effects in order 
			{
				int rpRegen = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBaseRpRegen);
				//static_cast<WORD>(skillData->SkillValue[index]);
				rpRegen *= setUnset;
				GetAttributesManager()->UpdateRPRegeneration(rpRegen, true);
				isBuff = true;
				sLog.outBasic("rpRegen %d", rpRegen);
				break;
			}
			case ACTIVE_MOVE_SPEED_UP://100%
			{
				float moveSpeedUp = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.fBaseRunSpeed);
				moveSpeedUp *= setUnset;
				sLog.outBasic("addSpeed %f", moveSpeedUp);
				GetAttributesManager()->UpdateRunSpeed(moveSpeedUp, true);
				isBuff = true;
				break;
			}
			case ACTIVE_ENERGY_OFFENCE_UP://100% 
			{
				/*int addEnergyOffence = GetAttributesManager()->GetPercent(skillData->SkillValue[index],
					static_cast<float>(GetPcProfile()->avatarAttribute.wLastEnergyOffence));*/
				int addEnergyOffence = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBaseEnergyOffence);
				addEnergyOffence *= setUnset;
				GetAttributesManager()->UpdateEnergyOffence(addEnergyOffence, true);
				isBuff = true;
				sLog.outBasic("addEnergyOffence %d", addEnergyOffence);
				break;
			}
			case ACTIVE_PHYSICAL_OFFENCE_UP://100% 
			{
				/*WORD addPhysicalOffence = GetAttributesManager()->GetPercent(skillData->SkillValue[index],
					static_cast<float>(GetPcProfile()->avatarAttribute.wLastPhysicalOffence));*/
				int addPhysicalOffence = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBasePhysicalOffence);

				addPhysicalOffence *= setUnset;
				GetAttributesManager()->UpdatePhysicalOffence(addPhysicalOffence, true);
				isBuff = true;
				sLog.outBasic("addPhysicalOffence %d", addPhysicalOffence);
				break;
			}			
			case ACTIVE_CON_UP:	//100% 	
			{
				int addConstitution = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.byBaseCon);
				addConstitution *= setUnset;
				sLog.outBasic("Add Constitution %d", addConstitution);
				GetAttributesManager()->UpdateCon(addConstitution, true);
				isBuff = true;
				break;
			}
			case ACTIVE_FOC_UP:	//100% 
			{
				int addFocus = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.byBaseFoc);
				addFocus *= setUnset;
				sLog.outBasic("Add Focus %d", addFocus);
				GetAttributesManager()->UpdateFoc(addFocus, true);
				isBuff = true;
				break;
			}
			case ACTIVE_ENG_UP:	//100
			{
				int addEnergy = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.byBaseEng);
				addEnergy *= setUnset;
				sLog.outBasic("Add Energy %d", addEnergy);
				GetAttributesManager()->UpdateEng(addEnergy, true);
				isBuff = true;
				break;
			}
			case ACTIVE_DEX_UP:	//100% 
			{
				int addDextery = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.byBaseDex);
				addDextery *= setUnset;
				sLog.outBasic("Add Dextery %d", addDextery);
				GetAttributesManager()->UpdateDex(addDextery, true);
				isBuff = true;
				break;
			}
			case ACTIVE_STR_UP:
			{
				int addStrength = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.byBaseStr);
				addStrength *= setUnset;
				sLog.outBasic("Add Strenght %d", addStrength);
				GetAttributesManager()->UpdateStr(addStrength, true);
				isBuff = true;
				break;
			}
			case ACTIVE_SOL_UP:
			{
				int addSoul = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.byBaseSol);
				addSoul *= setUnset;

				sLog.outBasic("Add Soul %d", addSoul);
				GetAttributesManager()->UpdateSol(addSoul, true);
				isBuff = true;
				break;
			}
			case ACTIVE_ENERGY_CRITICAL_DAMAGE_UP:
			{
				int energyCriticalDamage = skillData->SkillValue[index];
				energyCriticalDamage *= setUnset;
				sLog.outBasic("energyCriticalDamage %d", energyCriticalDamage);
				GetAttributesManager()->UpdateEnergyCriticalRange(energyCriticalDamage, true);
				isBuff = true;
				break;
			}
			case ACTIVE_PHYSICAL_CRITICAL_DAMAGE_UP:
			{
				int physicalCriticalDamage = skillData->SkillValue[index];
				physicalCriticalDamage *= setUnset;
				sLog.outBasic("energyCriticalDamage %d", physicalCriticalDamage);
				GetAttributesManager()->UpdatePhysicalCriticalRange(physicalCriticalDamage, true);
				isBuff = true;
				break;
			}
			case ACTIVE_PHYSICAL_CRITICAL:
			{
				int physicalCritical = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBasePhysicalCriticalRate);
				physicalCritical *= setUnset;
				sLog.outBasic("physicalCritical %d", physicalCritical);
				GetAttributesManager()->UpdatePhysicalCriticalRate(physicalCritical, true);
				isBuff = true;
				break;
			}
			case ACTIVE_ATTACK_RATE_UP:
			{
				int attackRate = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index],
					GetPcProfile()->avatarAttribute.wBaseAttackRate);
				attackRate *= setUnset;
				sLog.outBasic("attackRate %d", attackRate);
				GetAttributesManager()->UpdateHitRate(attackRate, true);
				isBuff = true;
				break;
			}
			case ACTIVE_DODGE_RATE_UP:
			{
				int dodgeRate = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.wBaseDodgeRate);
				dodgeRate *= setUnset;
				sLog.outBasic("dodgeRate %d", dodgeRate);
				GetAttributesManager()->UpdateDodgeRate(dodgeRate, true);
				isBuff = true;
				break;
			}
			case ACTIVE_ATTACK_SPEED_UP:
			{
				int attackSpeedRate = GetValueByEffectType(skillData->bySkill_Effect_Type[index], skillData->SkillValue[index], 
					GetPcProfile()->avatarAttribute.wBaseAttackSpeedRate);
				attackSpeedRate *= -1;
				attackSpeedRate *= setUnset;
				sLog.outBasic("attackSpeedRate %d", attackSpeedRate);
				GetAttributesManager()->UpdateAttackspeedRate(attackSpeedRate, true);
				isBuff = true;
				break;
			}
		}
	}
	sLog.outBasic("isBuff %d", isBuff);
	return isBuff;
}

void Player::GetAtributesCalculation(HOBJECT Target[32], BYTE MaxApplyTarget, BYTE byRPBonus, sSKILL_TBLDAT skillData)
{
	int TargetCount = 0;
	for (int D = 0; D < MaxApplyTarget; D++)
	{
		Object* ObjectInfo = static_cast<Object*>(GetFromList(Target[D]));
		if (ObjectInfo != NULL)
		{
			ObjectType = ObjectInfo->GetTypeId();
		}
		//player
		if (ObjectType == OBJTYPE_PC)
		{
			Player* PlayerInfo = static_cast<Player*>(GetFromList(Target[D]));
			if (PlayerInfo != NULL)
			{
				int CriticalRate = 0;
				int CriticalDefence = 0;
				float attack = 0;
				float damage = 0;
				int Defense = 0;
				float TotalCriticRatePercent = 0;
				//Demage Calculation		
				if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)// &&
					//skillData.bySkill_Effect_Type[1] == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_UNKNOWN)
				{
					sLog.outBasic("SKILL_ACTIVE_TYPE_DD");
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						sLog.outBasic("SKILL_TYPE_PHYSICAL");
						CriticalRate = GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate;
						CriticalDefence = PlayerInfo->GetPcProfile()->avatarAttribute.physicalCriticalDefenceRate;
						attack = GetPcProfile()->avatarAttribute.wLastPhysicalOffence;//+skillData.SkillValue[0];
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						damage = fightManager.CalculePhysicalDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						TotalCriticRatePercent = fightManager.CalculePhysicalCriticalSuccess(CriticalRate, CriticalDefence);
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						sLog.outBasic("SKILL_TYPE_ENERGY");
						CriticalRate = GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate;
						CriticalDefence = PlayerInfo->GetPcProfile()->avatarAttribute.energyCriticalDefenceRate;
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence;// +skillData.SkillValue[0];
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence;
						TotalCriticRatePercent = fightManager.CalculeEnergyCriticalSuccess(CriticalRate, CriticalDefence);
						damage = fightManager.CalculeEnergyDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						sLog.outBasic("SKILL_TYPE_STATE");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence + GetPcProfile()->avatarAttribute.wLastPhysicalOffence + skillData.SkillValue[0];
						attack /= 2.5;
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence + PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
				}
				//Skull Demage in Percent
				else if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
				{
					sLog.outBasic("SKILL_ACTIVE_TYPE_DOT");
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						sLog.outBasic("SKILL_TYPE_PHYSICAL");
						CriticalRate = GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate;
						attack = GetPcProfile()->avatarAttribute.wLastPhysicalOffence / 100 * skillData.SkillValue[0];
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						sLog.outBasic("SKILL_TYPE_ENERGY");
						CriticalRate = GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate;
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * skillData.SkillValue[0];
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence;
						attack /= 1.5;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						sLog.outBasic("SKILL_TYPE_STATE");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence + GetPcProfile()->avatarAttribute.wLastPhysicalOffence + skillData.SkillValue[0];
						attack /= 2.5;
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence + PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
				}
				else if (skillData.bySkill_Effect_Type[0] == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD && 
					skillData.bySkill_Effect_Type[1] == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
				{
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						CriticalRate = GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate;
						attack = GetPcProfile()->avatarAttribute.wLastPhysicalOffence;// +skillData.SkillValue[0] / 100 * skillData.SkillValue[1];
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						//attack /= 1.5;
						damage = fightManager.CalculePhysicalDamage(attack, GetPcProfile()->byLevel, Defense);
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;

					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						CriticalRate = GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate;
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence;// +skillData.SkillValue[0] / 100 * skillData.SkillValue[1]);
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence;
						//attack /= 1.5;
						damage = fightManager.CalculeEnergyDamage(attack, GetPcProfile()->byLevel, Defense);
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence + GetPcProfile()->avatarAttribute.wLastPhysicalOffence + skillData.SkillValue[0];
						attack /= 2.5;
						Defense = PlayerInfo->GetPcProfile()->avatarAttribute.wLastEnergyDefence + PlayerInfo->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
				}

				//Demage
				//float TotalAttack = attack + Defense;
				//float FinalPercent = attack * 100 / TotalAttack;
				SkillDemage[TargetCount] = damage;//CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);//attack * FinalPercent / 100;

				//DemageValue[Demagecount] / 100 *  GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
				//HitRate
				int HitRate = GetPcProfile()->avatarAttribute.wLastAttackRate;
				int DodgeRate = PlayerInfo->GetPcProfile()->avatarAttribute.wLastDodgeRate;
				//float TotalHitRate = HitRate + DodgeRate;
				float TotalHitRatePercent = fightManager.CalculeAttackSuccess(HitRate, DodgeRate, GetPcProfile()->byLevel, PlayerInfo->GetPcProfile()->byLevel);//HitRate * 100 / TotalHitRate;
				int RandomHit = rand() % 100;
				//TotalHitRatePercent *= 1.6;
				//printf("Total Hit Percent %f \n", TotalHitRatePercent);

				/*int BlockCriticalRate = PlayerInfo->GetPcProfile()->avatarAttribute.fCriticalBlockSuccessRate;
				float TotalCriticRate = CriticalRate + BlockCriticalRate;
				TotalCriticRatePercent = CriticalRate * 100 / TotalCriticRate;*/
				int RandomCriticHit = rand() % 100;
				//printf("Total Critic rate Percent %f \n", TotalCriticRatePercent);


				//RP Acion
				if (byRPBonus == eDBO_RP_BONUS_TYPE::DBO_RP_BONUS_TYPE_KNOCKDOWN)
				{
					sGU_CHAR_KNOCKDOWN state;

					state.wPacketSize = sizeof(sGU_CHAR_KNOCKDOWN) - 2;
					state.wOpCode = GU_CHAR_KNOCKDOWN;

					state.handle = PlayerInfo->GetHandle();
					AttackType[D] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_KNOCKDOWN;

					sWorld.SendToAll((char*)&state, sizeof(sGU_CHAR_KNOCKDOWN));

					sGU_UPDATE_CHAR_STATE res1;

					res1.wOpCode = GU_UPDATE_CHAR_STATE;
					res1.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

					res1.handle = PlayerInfo->GetHandle();

					res1.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_KNOCKDOWN;
					res1.sCharState.sCharStateDetail.sCharStateKnockdown.vShift.x = PlayerInfo->GetVectorPosition().x + 5;
					res1.sCharState.sCharStateDetail.sCharStateKnockdown.vShift.y = PlayerInfo->GetVectorPosition().y;
					res1.sCharState.sCharStateDetail.sCharStateKnockdown.vShift.z = PlayerInfo->GetVectorPosition().z;

					res1.sCharState.sCharStateBase.vCurLoc = res1.sCharState.sCharStateDetail.sCharStateKnockdown.vShift;

					res1.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
					res1.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
					res1.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().z;

					res1.sCharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = PlayerInfo->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId;
					res1.sCharState.sCharStateBase.dwConditionFlag = 0;
					res1.sCharState.sCharStateBase.dwStateTime = 0x01;

					res1.sCharState.sCharStateBase.isFighting = false;
					res1.sCharState.sCharStateBase.isFlying = false;


					sWorld.SendToAll((char*)&res1, sizeof(sGU_UPDATE_CHAR_STATE));

				}
				if (byRPBonus == eDBO_RP_BONUS_TYPE::DBO_RP_BONUS_TYPE_RESULT_PLUS)
				{
					SkillDemage[TargetCount] *= 2;
				}
				//Rates Hit/Critic/Dodge
				if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
				{
					if (RandomCriticHit >= 0 && RandomCriticHit <= TotalCriticRatePercent)
					{
						AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;

						
						if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD ||
							skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
						{
							if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
							{
								sLog.outBasic("SKILL_TYPE_PHYSICAL");
								SkillDemage[TargetCount] = fightManager.CalculePhysicalCriticalDamage(SkillDemage[TargetCount],
									GetPcProfile()->avatarAttribute.fLastPhysicalCriticalRange);
							}
							else if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
							{
								sLog.outBasic("SKILL_TYPE_ENERGY");
								SkillDemage[TargetCount] = fightManager.CalculeEnergyCriticalDamage(SkillDemage[TargetCount],
									GetPcProfile()->avatarAttribute.fLastEnergyCriticalRange);
							}
						}
						//SkillDemage[TargetCount] += CriticalDemage[D];
					}
					else
					{
						AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
					}
				}
				else
				{
					AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					SkillDemage[TargetCount] = 0;
				}
				if (SkillDemage[TargetCount] <= 0 || SkillDemage[D] > 1000000000)
				{
					SkillDemage[TargetCount] = 0;
				}



				TargetCount += 1;
			}
			//
		}
		//Mob
		if (ObjectType == OBJTYPE_MOB)
		{
			Mob* MobInfo = static_cast<Mob*>(GetFromList(Target[D]));
			if (MobInfo != NULL)
			{
				float attack = 0;
				float Defense = 0;
				float damage = 0;
				int CriticalRate = 0;
				int CriticalDefence = 0;
				float TotalCriticRatePercent = 0;
				//Demage Calculation
				if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)
				{
					sLog.outBasic("SKILL_ACTIVE_TYPE_DD");
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						sLog.outBasic("SKILL_TYPE_PHYSICAL");
						attack = GetPcProfile()->avatarAttribute.wLastPhysicalOffence;// +skillData.SkillValue[0];
						Defense = static_cast<float>(MobInfo->GetMobData().Basic_physical_defence);
						//int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						//float FinalPercent = attack * 100 / TotalAttack;
						sLog.outDebug("Mob %d defense %d float %d", MobInfo->GetMobData().MonsterID, MobInfo->GetMobData().Basic_physical_defence, Defense);
						damage = fightManager.CalculePhysicalDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						CriticalRate = GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate;
						CriticalDefence = MobInfo->GetMobData().physicalCriticalDefenseRate;
						TotalCriticRatePercent = fightManager.CalculePhysicalCriticalSuccess(CriticalRate, CriticalDefence);
						//SkillDemage[TargetCount] = attack - deffense;//attack * FinalPercent / 100;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						sLog.outBasic("SKILL_TYPE_ENERGY");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence;// +skillData.SkillValue[0];
						Defense = static_cast<float>(MobInfo->GetMobData().Basic_energy_defence);
						//int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						//float FinalPercent = attack * 100 / TotalAttack;
						sLog.outDebug("Mob %d defense %d float %f", MobInfo->GetMobData().MonsterID, MobInfo->GetMobData().Basic_energy_defence, Defense);
						damage = fightManager.CalculeEnergyDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						CriticalRate = GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate;
						CriticalDefence = MobInfo->GetMobData().energyCriticalDefenseRate;
						TotalCriticRatePercent = fightManager.CalculePhysicalCriticalSuccess(CriticalRate, CriticalDefence);
						//SkillDemage[TargetCount] = attack - deffense;//attack * FinalPercent / 100;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						sLog.outBasic("SKILL_TYPE_STATE");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence + GetPcProfile()->avatarAttribute.wLastPhysicalOffence;

						Defense = static_cast<float>(MobInfo->GetMobData().Basic_energy_defence + MobInfo->GetMobData().Basic_physical_defence);
						//float attack =  GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[0];
						//int TotalAttack = attack + Defense;
						//float FinalPercent = attack * 100 / TotalAttack;
						//SkillDemage[TargetCount] = attack - Defense;// attack * FinalPercent / 100;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
				}
				//Skull Demage in Percent
				else if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
				{
					sLog.outBasic("SKILL_ACTIVE_TYPE_DOT");
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						sLog.outBasic("SKILL_TYPE_PHYSICAL");
						attack = GetPcProfile()->avatarAttribute.wLastPhysicalOffence;// / 100 * skillData.SkillValue[0];
						Defense = MobInfo->GetMobData().Basic_physical_defence;
						//int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						//float FinalPercent = attack * 100 / TotalAttack;
						damage = fightManager.CalculePhysicalDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						//SkillDemage[TargetCount] = attack - Defense;//attack * FinalPercent / 100;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						sLog.outBasic("SKILL_TYPE_ENERGY");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence;// / 100 * skillData.SkillValue[0];
						Defense = MobInfo->GetMobData().Basic_energy_defence;
						//int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						//float FinalPercent = attack * 100 / TotalAttack;
						damage = fightManager.CalculeEnergyDamage(attack, GetPcProfile()->byLevel, Defense);
						damage = CalculeSkillDamage(skillData.bySkill_Effect_Type, skillData.SkillValue, damage);
						//SkillDemage[TargetCount] = attack - defense;// attack* FinalPercent / 100;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate;
					}
					if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						sLog.outBasic("SKILL_TYPE_STATE");
						attack = GetPcProfile()->avatarAttribute.wLastEnergyOffence + GetPcProfile()->avatarAttribute.wLastPhysicalOffence;

						Defense = MobInfo->GetMobData().Basic_energy_defence + MobInfo->GetMobData().Basic_physical_defence;
						//float attack =  GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[0];
						//int TotalAttack = attack + Defense;
						//float FinalPercent = attack * 100 / TotalAttack;
						//SkillDemage[TargetCount] = attack - Defense ;// attack* FinalPercent / 100;
						damage = attack - Defense;
						//CriticalDemage[TargetCount] = attack / 100 * GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate;
					}
				}

				SkillDemage[TargetCount] = damage;// attack* FinalPercent / 100;

				//HitRate
				int HitRate = GetPcProfile()->avatarAttribute.wLastAttackRate + 500;
				int DodgeRate = MobInfo->GetMobData().Dodge_rate;
				//float TotalHitRate = HitRate + DodgeRate;
				float TotalHitRatePercent = fightManager.CalculeAttackSuccess(HitRate, DodgeRate, GetPcProfile()->byLevel, MobInfo->GetMobData().Level);//HitRate * 100 / TotalHitRate;
				int RandomHit = rand() % 100;
				//printf("Total Hit Percent %f \n", TotalHitRatePercent);

				/*int BlockCriticalRate = MobInfo->GetMobData().Block_rate;
				float TotalCriticRate = GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate + BlockCriticalRate;
				TotalCriticRatePercent = BlockCriticalRate * 100 / TotalCriticRate;*/
				int RandomCriticHit = rand() % 100;
				//	printf("Total Critic rate Percent %f \n", TotalCriticRatePercent);


				if (byRPBonus == eDBO_RP_BONUS_TYPE::DBO_RP_BONUS_TYPE_KNOCKDOWN)
				{
					sGU_CHAR_KNOCKDOWN state;

					state.wPacketSize = sizeof(sGU_CHAR_KNOCKDOWN) - 2;
					state.wOpCode = GU_CHAR_KNOCKDOWN;

					state.handle = MobInfo->GetHandle();
					AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_KNOCKDOWN;

					sWorld.SendToAll((char*)&state, sizeof(sGU_CHAR_KNOCKDOWN));
				}
				if (byRPBonus == eDBO_RP_BONUS_TYPE::DBO_RP_BONUS_TYPE_RESULT_PLUS)
				{
					SkillDemage[TargetCount] *= 2;
				}
				//Rates ~Hit/critic/Dodge
				if (RandomHit <= TotalHitRatePercent && TotalHitRatePercent > 0)
				{
					if (RandomCriticHit >= 0 && RandomCriticHit <= TotalCriticRatePercent)
					{
						AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;
						if (skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD ||
							skillData.bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
						{
							if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
							{
								sLog.outBasic("SKILL_TYPE_PHYSICAL");
								SkillDemage[TargetCount] = fightManager.CalculePhysicalCriticalDamage(SkillDemage[TargetCount],
									GetPcProfile()->avatarAttribute.fLastPhysicalCriticalRange);
							}
							else if (skillData.bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
							{
								sLog.outBasic("SKILL_TYPE_ENERGY");
								SkillDemage[TargetCount] = fightManager.CalculeEnergyCriticalDamage(SkillDemage[TargetCount],
									GetPcProfile()->avatarAttribute.fLastEnergyCriticalRange);
							}
						}
						//SkillDemage[TargetCount] *= 2;
						//SkillDemage[TargetCount] += CriticalDemage[TargetCount];
					}
					else
					{
						AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
					}
				}
				else
				{
					AttackType[TargetCount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					SkillDemage[TargetCount] = 0;
				}
				if (SkillDemage[TargetCount] <= 0 || SkillDemage[TargetCount] > 1000000000)
				{
					SkillDemage[TargetCount] = 0;
				}

				TargetCount += 1;
			}
		}

	}

}

void Player::UpdateEP(WORD curEP)
{
	sGU_UPDATE_CHAR_EP nfy;
	nfy.wOpCode = GU_UPDATE_CHAR_EP;
	nfy.wPacketSize = sizeof(sGU_UPDATE_CHAR_EP) - 2;
	nfy.handle = GetHandle();
	nfy.dwLpEpEventId = -1;
	nfy.wCurEP = curEP;
	nfy.wMaxEP = GetPcProfile()->avatarAttribute.wLastMaxEP;
	SendPacket((char*)&nfy, sizeof(sGU_UPDATE_CHAR_EP));
}

void Player::SkillAcion()
{

	sUG_CHAR_SKILL_REQ* pCharSkillReq = (sUG_CHAR_SKILL_REQ*)packets.GetPacketBuffer();

	sLog.outBasic("My handle %d handle skill %d count %d", GetHandle(), pCharSkillReq->hTarget, pCharSkillReq->byApplyTargetCount);
	for (int i = 0; i < pCharSkillReq->byApplyTargetCount; i++)
	{
		sLog.outBasic("Handle target %d", pCharSkillReq->ahApplyTarget[i]);
	}

	sGU_CHAR_SKILL_RES sSkil;
	sSkil.wPacketSize = sizeof(sGU_CHAR_SKILL_RES) - 2;
	sSkil.wOpCode = GU_CHAR_SKILL_RES;
	sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;

	bool bleed = false;
	bool isBuff = false;
	int skillID = skillManager.getIdAtPos(pCharSkillReq->bySlotIndex);
	SkillTable* skillTable = sTBM.GetSkillTable();
	sSKILL_TBLDAT* skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
	if (skillDataOriginal != NULL)
	{
		if (GetPcProfile()->wCurEP < skillDataOriginal->wRequire_EP)
		{
			sSkil.wResultCode = GAME_SKILL_NOT_ENOUGH_EP;
			SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
			return;
		}

		if (GetIsDead() == false)
		{
			sGU_CHAR_ACTION_SKILL skillRes;
			memset(&skillRes, 0, sizeof(sGU_CHAR_ACTION_SKILL));
			skillRes.wPacketSize = sizeof(sGU_CHAR_ACTION_SKILL) - 2;
			skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
			skillRes.wResultCode = GAME_SKILL_CANT_CAST_NOW;
			BuffTypeSkill pBuffData;
			memset(&pBuffData, 0, sizeof(BuffTypeSkill));
			pBuffData.OpCode = GU_BUFF_REGISTERED;
			pBuffData.size = sizeof(BuffTypeSkill) - 2;
			pBuffData.tblidx = INVALID_TBLIDX;
			int damageApply = 1;
			for (int Effect = 0; Effect < 2; Effect++)
			{
				////Skill Handle
				int count = 0;
				sSYSTEM_EFFECT_TBLDAT* SystemEffectData = NULL;
				SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(skillDataOriginal->skill_Effect[Effect]);

				if (SystemEffectData != NULL)
				{
					sLog.outBasic("Skill EffectCode %d Skill value %f skill tblidx %d", 
						SystemEffectData->effectCode, skillDataOriginal->SkillValue[Effect], skillDataOriginal->tblidx);
					switch (SystemEffectData->effectCode)
					{
					case ACTIVE_DIRECT_DAMAGE:
					case ACTIVE_BACKSTAB:
					case ACTIVE_WARP_BACK_ATTACK:
					case ACTIVE_CRITICAL_ATTACK:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										skillRes.aSkillResult[count].hTarget = PlayerInfo->GetHandle();
										skillRes.aSkillResult[count].byAttackResult = AttackType[count];

										skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
										skillRes.aSkillResult[count].effectResult[Effect].Value1 = SkillDemage[count] * damageApply;
										skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
										skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
										skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
										skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
										skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
										skillRes.aSkillResult[count].byBlockedAction = 255;
										skillRes.aSkillResult[count].vShift = PlayerInfo->GetVectorPosition();
										skillRes.aSkillResult[count].vShift1 = PlayerInfo->GetVectorPosition();
										skillRes.bySkillResultCount = count + 1;
										damageApply = 0;

										PlayerInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
										count = 1;
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{

									skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
									skillRes.aSkillResult[count].byAttackResult = AttackType[count];

									skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
									skillRes.aSkillResult[count].effectResult[Effect].Value1 = SkillDemage[count] * damageApply;
									skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
									skillRes.aSkillResult[count].byBlockedAction = 255;
									//skillRes.aSkillResult[count].vShift = MobInfo->GetVectorPosition();
									//skillRes.aSkillResult[count].vShift1 = MobInfo->GetVectorPosition();
									skillRes.bySkillResultCount = count + 1;
									damageApply = 0;

									//if (MobInfo->attackers == 0)
									MobInfo->attackers = GetHandle();
									MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
									count += 1;
								}
							}
						}
						break;
					}
					case ACTIVE_BLEED:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = skillDataOriginal->byAppoint_Target;

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											bleed = true;
											pBuffData.hHandle = PlayerInfo->GetHandle();
											//pBuffData.slot = 1;
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;//Time

											float BleedDemage = SkillDemage[i] / 2;
											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = BleedDemage;
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = BleedDemage;

											if (pBuffData.BuffInfo[Effect].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[Effect].dwSystemEffectValue > 1000000)
											{
												pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
												pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
											}
											if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
											{
												SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
												SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
											}
											//Handle Buff Time List
											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													//printf("Regist new buff \n");
													FreePlace = i;
												}

											}
											PlayerInfo->ExecuteEffectCalculation(pBuffData.tblidx, false);

											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].isAffectPlayer = true;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectType = skillDataOriginal->skill_Effect[Effect];
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectValue[0] = pBuffData.BuffInfo[Effect].SystemEffectValue;
											GetAttributesManager()->sBuffTimeInfo[FreePlace].isMob = false;
										}
										count += 1;
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL)
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										bleed = true;
										pBuffData.hHandle = MobInfo->GetHandle();
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;//Time
										float BleedDemage = SkillDemage[i] / 2;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = BleedDemage;
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect] + GetPcProfile()->avatarAttribute.fDotValueChangePercent;
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										//Handle Buff Time List
										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												//printf("Regist new buff \n");
												FreePlace = i;
											}

										}
										ExecuteEffectCalculation(pBuffData.tblidx, false);

										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].isAffectPlayer = true;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectType = skillDataOriginal->skill_Effect[Effect];
										GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectValue[0] = pBuffData.BuffInfo[Effect].SystemEffectValue;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].isMob = true;
									}
								}
							}
						}

						break;
					}
					case ACTIVE_POISON:
					case ACTIVE_STOMACHACHE:
					case ACTIVE_BURN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = skillDataOriginal->byAppoint_Target;

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											bleed = true;
											pBuffData.hHandle = PlayerInfo->GetHandle();
											//pBuffData.slot = 1;
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
											float BleedDemage = SkillDemage[i] / 2;
											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = BleedDemage;
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = BleedDemage;

											if (pBuffData.BuffInfo[Effect].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[Effect].dwSystemEffectValue > 100000)
											{
												pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
												pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
											}
											if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
											{
												SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
												SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
											}
											//Handle Buff Time List
											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													//printf("Regist new buff \n");
													FreePlace = i;
												}

											}
											PlayerInfo->ExecuteEffectCalculation(pBuffData.tblidx, false);

											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].isAffectPlayer = true;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectType = skillDataOriginal->skill_Effect[Effect];
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectValue[0] = pBuffData.BuffInfo[Effect].SystemEffectValue;
										}
										count += 1;
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL)
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										bleed = true;
										pBuffData.hHandle = MobInfo->GetHandle();
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
										float BleedDemage = SkillDemage[i] / 2;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = BleedDemage;
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs + GetPcProfile()->avatarAttribute.fKeepTimeChangePercent;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = BleedDemage;
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										//Handle Buff Time List
										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												//printf("Regist new buff \n");
												FreePlace = i;
											}

										}
										ExecuteEffectCalculation(pBuffData.tblidx, false);

										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].isAffectPlayer = true;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectType = skillDataOriginal->skill_Effect[Effect];
										GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectValue[0] = pBuffData.BuffInfo[Effect].SystemEffectValue;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].isMob = true;
									}
								}
							}
						}

						break;
					}
					case ACTIVE_DIRECT_HEAL:
					{
						sLog.outDebug("Skill: ACTIVE_DIRECT_HEAL");

						//New system
						RunScriptDendeQuest(pCharSkillReq->hTarget);
						/*NTL_TS_T_ID questId = GetQuestManager()->FindQuestByNPCSpawned(pCharSkillReq->hTarget);
						QuestData* quest = GetQuestManager()->FindQuestById(questId);
						if (quest)
						{
							sLog.outBasic("New sytem: NpcHandle %d questId %d", pCharSkillReq->hTarget, quest->QuestID);
							Npc* NpcInfoSrc = static_cast<Npc*>(GetFromList(GetAttributesManager()->questSubCls.npcHandle));
							if (NpcInfoSrc)
							{
								sLog.outBasic("New system: Npc found! %d %d skilltarget %d", NpcInfoSrc->GetHandle(), quest->questSubCls.npcHandle, pCharSkillReq->hTarget);
							}
						}
						//New system

						// Sub class dende
						Npc* NpcInfoSrc = static_cast<Npc*>(GetFromList(GetAttributesManager()->questSubCls.npcHandle));
						if (NpcInfoSrc)
						{
							sLog.outDebug("Npc found! %d %d skilltarget %d", NpcInfoSrc->GetHandle(), GetAttributesManager()->questSubCls.npcHandle, pCharSkillReq->hTarget);

							NpcInfoSrc->GetState()->sCharStateDetail.sCharStateDirectPlay.byDirectPlayType = DIRECT_PLAY_NORMAL;

							Timer.setTimeout([&](Npc* NpcInfo) {

								if (NpcInfo)
								{
									NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx = 60002;
									NpcInfo->UpdateState(eCHARSTATE::CHARSTATE_DIRECT_PLAY);

									sGU_CHAR_DIALOG dialog;
									memset(&dialog, 0, sizeof sGU_CHAR_DIALOG);
									dialog.wPacketSize = sizeof(sGU_CHAR_DIALOG) - 2;
									dialog.wOpCode = GU_CHAR_DIALOG;
									dialog.hSubject = NpcInfo->GetHandle();
									dialog.byDialogType = eCHAR_DIALOG_TYPE::CHAR_DIALOG_SAY;
									dialog.textTblidx = 3313;
									SendPacket((char*)&dialog, sizeof(sGU_CHAR_DIALOG));
									sLog.outDebug("DIRECT_PLAY_NORMAL %d", NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx);
								}
								}, 5000, NpcInfoSrc);

							Timer.setTimeout([&](Npc* NpcInfo) {
								if (NpcInfo)
								{
									NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx = 60003;
									NpcInfo->UpdateState(eCHARSTATE::CHARSTATE_DIRECT_PLAY);

									sGU_CHAR_DIALOG dialog;
									memset(&dialog, 0, sizeof sGU_CHAR_DIALOG);
									dialog.wPacketSize = sizeof(sGU_CHAR_DIALOG) - 2;
									dialog.wOpCode = GU_CHAR_DIALOG;
									dialog.hSubject = NpcInfo->GetHandle();
									dialog.byDialogType = eCHAR_DIALOG_TYPE::CHAR_DIALOG_SAY;
									dialog.textTblidx = 3314;
									SendPacket((char*)&dialog, sizeof(sGU_CHAR_DIALOG));
									sLog.outDebug("DIRECT_PLAY_NORMAL %d", NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx);
								}
								}, 10000, NpcInfoSrc);

							Timer.setTimeout([&](Npc* NpcInfo) {

								NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx = 60004;
								NpcInfo->UpdateState(eCHARSTATE::CHARSTATE_DIRECT_PLAY);
								sLog.outDebug("DIRECT_PLAY_NORMAL %d", NpcInfo->GetState()->sCharStateDetail.sCharStateDirectPlay.directTblidx);
								}, 15000, NpcInfoSrc);

							Timer.setTimeout([&](Npc* NpcInfo) {
								if (NpcInfo)
								{
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.dwTimeStamp = 0;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.byMoveFlag = 1;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.bHaveSecondDestLoc = false;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.unknown = 0;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.byDestLocCount = 1;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].x = 5779.3789;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].y = -90.417999;
									NpcInfo->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0].z = 3999.4399;
									NpcInfo->UpdateState(eCHARSTATE::CHARSTATE_DESTMOVE);
								}
								}, 20000, NpcInfoSrc);

							Timer.setTimeout([&](Npc* NpcInfo) {
								if (NpcInfo)
								{
									sGU_OBJECT_DESTROY sPacket;

									sPacket.wOpCode = GU_OBJECT_DESTROY;
									sPacket.handle = NpcInfo->GetHandle();
									sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

									SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
									NpcInfo->SetIsBecomeMob(true);
									NpcInfo->RemoveFromWorld();
									RemoveFromList(*NpcInfo);
									sLog.outDebug("NPC deleted");
								}
								}, 30000, NpcInfoSrc);
						}
						else
						{
							sLog.outDebug("Npc not found!");
						}*/
						// Sub class dende

						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
						if (pCharSkillReq->hTarget == GetHandle())
						{
							skillRes.aSkillResult[count].hTarget = GetHandle();
							skillRes.aSkillResult[count].byAttackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
							float HealPercent = GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * 35;
							skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DH_HOT;
							skillRes.aSkillResult[count].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect] + HealPercent;
							skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
							skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
							skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
							skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
							skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
							skillRes.aSkillResult[count].byBlockedAction = 255;
							skillRes.aSkillResult[count].vShift = GetVectorPosition();
							skillRes.aSkillResult[count].vShift1 = GetVectorOriantation();
							skillRes.bySkillResultCount = count + 1;
							int newlp = GetPcProfile()->dwCurLP;
							if (newlp <= GetPcProfile()->avatarAttribute.wLastMaxLP)
							{
								newlp += skillRes.aSkillResult[count].effectResult[Effect].Value1;
							}
							if (newlp >= GetPcProfile()->avatarAttribute.wLastMaxLP)
							{
								newlp = GetPcProfile()->avatarAttribute.wLastMaxLP;
							}
							sGU_UPDATE_CHAR_LP LPs;
							LPs.wOpCode = GU_UPDATE_CHAR_LP;
							LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
							GetPcProfile()->dwCurLP = newlp;
							LPs.dwLpEpEventId = 0;
							LPs.handle = GetHandle();
							LPs.wCurLP = GetPcProfile()->dwCurLP;
							LPs.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
							SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
							SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
							count = 1;
						}
						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && GetAttributesManager()->PlayerInFreeBatle == false)
								{
									skillRes.aSkillResult[count].hTarget = PlayerInfo->GetHandle();
									skillRes.aSkillResult[count].byAttackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
									float HealPercent = GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * 35;
									skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DH_HOT;
									skillRes.aSkillResult[count].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect] + HealPercent;
									skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
									skillRes.aSkillResult[count].byBlockedAction = 255;
									skillRes.aSkillResult[count].vShift = PlayerInfo->GetVectorPosition();
									skillRes.aSkillResult[count].vShift1 = PlayerInfo->GetVectorOriantation();
									skillRes.bySkillResultCount = count + 1;
									int newlp = PlayerInfo->GetPcProfile()->dwCurLP;
									if (newlp <= PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxLP)
									{
										newlp += skillRes.aSkillResult[count].effectResult[Effect].Value1;
									}
									if (newlp >= PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxLP)
									{
										newlp = PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxLP;
									}
									sGU_UPDATE_CHAR_LP LPs;
									LPs.wOpCode = GU_UPDATE_CHAR_LP;
									LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
									PlayerInfo->GetPcProfile()->dwCurLP = newlp;
									LPs.dwLpEpEventId = 0;
									LPs.handle = PlayerInfo->GetHandle();
									LPs.wCurLP = PlayerInfo->GetPcProfile()->dwCurLP;
									LPs.wMaxLP = PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxLP;
									PlayerInfo->SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
									PlayerInfo->SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
									count = 1;
								}
							}
							else if (ObjectType == OBJTYPE_NPC)
							{
								Npc* NpcInfo = static_cast<Npc*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (NpcInfo != NULL)
								{
									skillRes.aSkillResult[count].hTarget = NpcInfo->GetHandle();
									skillRes.aSkillResult[count].byAttackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
									float HealPercent = GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * 35;
									skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DH_HOT;
									skillRes.aSkillResult[count].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect] + HealPercent;
									skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
									skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
									skillRes.aSkillResult[count].byBlockedAction = 255;
									skillRes.aSkillResult[count].vShift = NpcInfo->GetVectorPosition();
									skillRes.aSkillResult[count].vShift1 = NpcInfo->GetVectorOriantation();
									skillRes.bySkillResultCount = count + 1;
									int newlp = NpcInfo->GetNpcData().CurLP;
									if (newlp <= NpcInfo->GetNpcData().MaxLP)
									{
										newlp += skillRes.aSkillResult[count].effectResult[Effect].Value1;
									}
									if (newlp >= NpcInfo->GetNpcData().MaxLP)
									{
										newlp = NpcInfo->GetNpcData().MaxLP;
									}
									sGU_UPDATE_CHAR_LP LPs;
									LPs.wOpCode = GU_UPDATE_CHAR_LP;
									LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
									NpcInfo->GetNpcData2()->CurLP = newlp;
									LPs.dwLpEpEventId = 0;
									LPs.handle = NpcInfo->GetHandle();
									LPs.wCurLP = NpcInfo->GetNpcData().CurLP;
									LPs.wMaxLP = NpcInfo->GetNpcData().MaxLP;;

									SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
									SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));

									count = 1;
								}
							}
						}
						break;
					}
					case ACTIVE_SUPER_SAIYAN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
						UpdateAspectState(eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN);
						break;
					}
					case ACTIVE_PURE_MAJIN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_PURE_MAJIN;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
						UpdateAspectState(eASPECTSTATE::ASPECTSTATE_PURE_MAJIN);
						break;
					}
					case ACTIVE_KAIOKEN:
					{
						if (GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount >= 100)
						{
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount = 0;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;
						}
						if (GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount >= 3 && GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount <= 4)
						{
							//You Get Kaioken Limitacion
						}
						else
						{
							sSkil.wResultCode = GAME_SUCCESS;

							skillRes.skillId = skillDataOriginal->tblidx;
							skillRes.wResultCode = GAME_SUCCESS;
							skillRes.byRpBonusType = 0;//Untested
							skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
							skillRes.handle = GetHandle();//My Handle
							skillRes.hAppointedTarget = GetHandle();
							GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_KAIOKEN;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount += 1;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;

							UpdateAspectState(eASPECTSTATE::ASPECTSTATE_KAIOKEN);
							//	 GetAttributesManager()->SetLastPhysicalOffence(50);
							// GetAttributesManager()->SetLastEnergyOffence(50);						
						}
						break;
					}
					case ACTIVE_GREAT_NAMEK:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_GREAT_NAMEK;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
						GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
						UpdateAspectState(eASPECTSTATE::ASPECTSTATE_GREAT_NAMEK);
						break;
					}
					case ACTIVE_MAX_LP_UP://100% 						
					case ACTIVE_MAX_EP_UP://100% 
					case ACTIVE_MAX_RP_UP://100% 
					case ACTIVE_PHYSICAL_DEFENCE_UP://100% 
					case ACTIVE_ENERGY_DEFENCE_UP://100% 
					case ACTIVE_BLOCK_RATE_UP://100% 
					{
						break;
					}
					//case ACTIVE_LP_REGENERATION://need Handle the effect is here to try do effects in order 
					//case ACTIVE_EP_REGENERATION://need Handle the effect is here to try do effects in order 
					case ACTIVE_ENERGY_CRITICAL:
					case ACTIVE_SKILL_CASTING_TIME_DOWN:
					{
						break;
					}
					case ACTIVE_STONE:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
											state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_STONE;

											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//	printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
										state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_STONE;

										MobInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//	printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_CANDY:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
											state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_CANDY;

											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//	printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
										state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_CANDY;

										MobInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//	printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_SLEEP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_SLEEPING);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SLEEPING;


											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//	printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SLEEPING;

										MobInfo->SetState(eCHARSTATE::CHARSTATE_SLEEPING);
										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//	printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_PARALYZE:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_PARALYZED);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_PARALYZED;


											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//	printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_PARALYZED;

										MobInfo->SetState(eCHARSTATE::CHARSTATE_PARALYZED);
										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//	printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_WARP_STUN:
					case ACTIVE_STUN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();

											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].StunedType = CHARSTATE_STUNNED;
											PlayerInfo->GetState()->sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
											PlayerInfo->GetState()->sCharStateBase.dwConditionFlag = 0;
											PlayerInfo->GetState()->sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_GENERAL;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
											state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_GENERAL;

											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										MobInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;


										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_FREEZE:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							//	printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);
							if (ObjectType == OBJTYPE_PC)
							{
								Player* PlayerInfo = static_cast<Player*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (PlayerInfo != NULL && PlayerInfo->GetIsDead() == false)
								{
									if (PlayerInfo->GetAttributesManager()->IsinPVP == true || PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == true)
									{
										if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
										{
											pBuffData.hHandle = PlayerInfo->GetHandle();
											pBuffData.tblidx = skillDataOriginal->tblidx;
											pBuffData.bySourceType = 0;
											pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

											pBuffData.isactive = 1;
											pBuffData.Type = 0;
											pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
											pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
											pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

											int FreePlace = 0;
											for (int i = 0; i <= 32; i++)
											{
												if (PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || PlayerInfo->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
												{
													FreePlace = i;
												}

											}
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
											PlayerInfo->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
											PlayerInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
											sGU_UPDATE_CHAR_STATE state;

											state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
											state.wOpCode = GU_UPDATE_CHAR_STATE;

											state.handle = PlayerInfo->GetHandle();
											state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
											state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_FROZEN;

											state.sCharState.sCharStateBase.vCurLoc.x = PlayerInfo->GetVectorPosition().x;
											state.sCharState.sCharStateBase.vCurLoc.y = PlayerInfo->GetVectorPosition().y;
											state.sCharState.sCharStateBase.vCurLoc.z = PlayerInfo->GetVectorPosition().z;
											state.sCharState.sCharStateBase.vCurDir.x = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.vCurDir.y = PlayerInfo->GetVectorOriantation().y;
											state.sCharState.sCharStateBase.vCurDir.z = PlayerInfo->GetVectorOriantation().x;
											state.sCharState.sCharStateBase.dwConditionFlag = 0;
											//	res.sCharState.sCharStateBase.bFightMode = false;
											state.sCharState.sCharStateBase.dwStateTime = 2;

											PlayerInfo->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
											PlayerInfo->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										}
										count = 1;
										//	printf("count %d \n", count);
									}
								}
							}
							if (ObjectType == OBJTYPE_MOB)
							{
								Mob* MobInfo = static_cast<Mob*>(GetFromList(pCharSkillReq->ahApplyTarget[i]));
								if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
								{
									if (AttackType[count] != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
									{
										pBuffData.hHandle = MobInfo->GetHandle();

										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
										pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												FreePlace = i;
											}

										}
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										//if (MobInfo->attackers == 0)
										MobInfo->attackers = GetHandle();
										sGU_UPDATE_CHAR_STATE state;

										state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
										state.wOpCode = GU_UPDATE_CHAR_STATE;

										state.handle = MobInfo->GetHandle();
										state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_STUNNED;
										state.sCharState.sCharStateDetail.sCharStateStunned.byStunType = eDBO_STUN_TYPE::DBO_STUN_TYPE_FROZEN;

										MobInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
										state.sCharState.sCharStateBase.vCurLoc.x = MobInfo->GetVectorPosition().x;
										state.sCharState.sCharStateBase.vCurLoc.y = MobInfo->GetVectorPosition().y;
										state.sCharState.sCharStateBase.vCurLoc.z = MobInfo->GetVectorPosition().z;
										state.sCharState.sCharStateBase.vCurDir.x = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.vCurDir.y = MobInfo->GetVectorOriantation().y;
										state.sCharState.sCharStateBase.vCurDir.z = MobInfo->GetVectorOriantation().x;
										state.sCharState.sCharStateBase.dwConditionFlag = 0;
										//	res.sCharState.sCharStateBase.bFightMode = false;
										state.sCharState.sCharStateBase.dwStateTime = 2;

										SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
										SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

									}
									count += 1;
									//	printf("count %d \n", count);
								}
							}
						}
						break;
					}
					case ACTIVE_ENERGY_REFLECTION:
					case ACTIVE_FAKE_DEATH:
					case ACTIVE_BATTLE_INABILITY:
					case ACTIVE_SKILL_INABILITY:
					case ACTIVE_CONFUSE:
					case ACTIVE_TERROR:
					case ACTIVE_MAX_LP_DOWN:
					case ACTIVE_MAX_EP_DOWN:
					case ACTIVE_MAX_RP_DOWN:
					case ACTIVE_PHYSICAL_OFFENCE_DOWN:
					case ACTIVE_ENERGY_OFFENCE_DOWN:
					case ACTIVE_CON_DOWN:
					case ACTIVE_MOVE_SPEED_DOWN:
					{
						break;
					}
					case ACTIVE_SPINNING_ATTACK:
					{
						sSkil.wResultCode = GAME_SUCCESS;
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.skillId = skillDataOriginal->tblidx;
						sLog.outBasic("Skillid %d", skillDataOriginal->tblidx);
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.dwLpEpEventId = 1712247496;
						skillRes.byRpBonusType = -1;//Untested
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						skillRes.bIsSkillHarmful = 0;
						skillRes.bySkillResultCount = 1;
						skillRes.aSkillResult[count].hTarget = GetHandle();
						skillRes.aSkillResult[count].byAttackResult = 0;
						skillRes.aSkillResult[count].effectResult[Effect].eResultType = 255;
						skillRes.aSkillResult[count].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
						skillRes.aSkillResult[count].effectResult[1].eResultType = 255;
						skillRes.aSkillResult[count].byBlockedAction = -1;
						skillRes.aSkillResult[count].unk1 = 0;
						skillRes.aSkillResult[count].vShift1 = m_position;

						GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_SPINNING_ATTACK;
						memset(&GetState()->sCharStateBase.aspectState.sAspectStateDetail, 0, sizeof GetState()->sCharStateBase.aspectState.sAspectStateDetail);
						
						GetAttributesManager()->spinInfo.spinTime = GetTickCount();
						GetAttributesManager()->spinInfo.spinEndTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						GetAttributesManager()->spinInfo.bySkill_Effect_Type[Effect] = skillDataOriginal->bySkill_Effect_Type[Effect];
						GetAttributesManager()->spinInfo.SkillValue[Effect] = skillDataOriginal->SkillValue[Effect];
						GetAttributesManager()->spinInfo.distance = GetPcProfile()->avatarAttribute.fLastAttackRange;
						GetAttributesManager()->spinInfo.skillId = skillDataOriginal->tblidx;
						GetAttributesManager()->spinInfo.spinMilisecond = 1000;

						if (pCharSkillReq->hTarget == GetHandle())
						{
							pBuffData.hHandle = GetHandle();
							//pBuffData.slot = 1;
							pBuffData.tblidx = skillDataOriginal->tblidx;
							pBuffData.bySourceType = 0;
							pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
							pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

							pBuffData.isactive = 1;
							pBuffData.Type = 0;
							pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
							pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
							pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
							//Handle Buff Time List
							int FreePlace = 0;
							for (int i = 0; i <= 32; i++)
							{
								if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == pBuffData.tblidx)
								{
									sGU_BUFF_DROPPED dropbuff;
									dropbuff.wOpCode = GU_BUFF_DROPPED;
									dropbuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
									dropbuff.hHandle = GetHandle();
									dropbuff.bySourceType = eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL;
									dropbuff.Slot = 0;
									dropbuff.tblidx = pBuffData.tblidx;
									dropbuff.unk1 = 0;
									SendPacket((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
									SendToPlayerList((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
									GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive = false;
									GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime = INVALID_TBLIDX;
									GetAttributesManager()->sBuffTimeInfo[i].BuffTime = INVALID_TBLIDX;
									GetAttributesManager()->sBuffTimeInfo[i].BuffID = INVALID_TBLIDX;
									ExecuteEffectCalculation(pBuffData.tblidx, true);
									//printf("Alardy got that buff \n");
									FreePlace = i;
								}
								//GetFreeSlot
								else if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
								{
									//	printf("Regist new buff \n");
									FreePlace = i;
								}

							}

							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
						}
						break;
					}
					case ACTIVE_ROLLING_ATTACK:
					{
						sSkil.wResultCode = GAME_SUCCESS;
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.skillId = skillDataOriginal->tblidx;
						sLog.outBasic("Skillid %d", skillDataOriginal->tblidx);
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.dwLpEpEventId = 1712247496;
						skillRes.byRpBonusType = -1;//Untested
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						skillRes.bIsSkillHarmful = 0;
						skillRes.bySkillResultCount = 1;
						skillRes.aSkillResult[count].hTarget = GetHandle();
						skillRes.aSkillResult[count].byAttackResult = 0;
						skillRes.aSkillResult[count].effectResult[Effect].eResultType = 255;
						skillRes.aSkillResult[count].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[0];
						skillRes.aSkillResult[count].effectResult[1].eResultType = 255;
						skillRes.aSkillResult[count].byBlockedAction = -1;
						skillRes.aSkillResult[count].unk1 = 0;
						skillRes.aSkillResult[count].vShift1 = m_position;

						GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_BALL;
						memset(&GetState()->sCharStateBase.aspectState.sAspectStateDetail, 0, sizeof GetState()->sCharStateBase.aspectState.sAspectStateDetail);
						
						GetAttributesManager()->spinInfo.spinTime = GetTickCount();
						GetAttributesManager()->spinInfo.spinEndTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						GetAttributesManager()->spinInfo.bySkill_Effect_Type[Effect] = skillDataOriginal->bySkill_Effect_Type[Effect];
						GetAttributesManager()->spinInfo.SkillValue[Effect] = skillDataOriginal->SkillValue[Effect];
						GetAttributesManager()->spinInfo.distance = GetPcProfile()->avatarAttribute.fLastAttackRange;
						GetAttributesManager()->spinInfo.skillId = skillDataOriginal->tblidx;
						GetAttributesManager()->spinInfo.spinMilisecond = 1000;

						if (pCharSkillReq->hTarget == GetHandle())
						{
							pBuffData.hHandle = GetHandle();
							//pBuffData.slot = 1;
							pBuffData.tblidx = skillDataOriginal->tblidx;
							pBuffData.bySourceType = 0;
							pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
							pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

							pBuffData.isactive = 1;
							pBuffData.Type = 0;
							pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
							pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
							pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
							//Handle Buff Time List
							int FreePlace = 0;
							for (int i = 0; i <= 32; i++)
							{
								if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == pBuffData.tblidx)
								{
									sGU_BUFF_DROPPED dropbuff;
									dropbuff.wOpCode = GU_BUFF_DROPPED;
									dropbuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
									dropbuff.hHandle = GetHandle();
									dropbuff.bySourceType = eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL;
									dropbuff.Slot = 0;
									dropbuff.tblidx = pBuffData.tblidx;
									dropbuff.unk1 = 0;
									SendPacket((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
									SendToPlayerList((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
									GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive = false;
									GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime = INVALID_TBLIDX;
									GetAttributesManager()->sBuffTimeInfo[i].BuffTime = INVALID_TBLIDX;
									GetAttributesManager()->sBuffTimeInfo[i].BuffID = INVALID_TBLIDX;
									ExecuteEffectCalculation(pBuffData.tblidx, true);
									//printf("Alardy got that buff \n");
									FreePlace = i;
								}
								//GetFreeSlot
								else if (GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
								{
									//	printf("Regist new buff \n");
									FreePlace = i;
								}

							}

							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
							GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
						}
						break;
					}
					case ACTIVE_SUMMON:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						printf("SkillValue %d \n", skillDataOriginal->SkillValue[Effect]);

						break;
					}
					case ACTIVE_TELEPORT_BIND:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = GetHandle();//My Handle
						skillRes.hAppointedTarget = GetHandle();
						TeleportToPopo();
						break;
					}
					//NEXT CASE
					}
				}
				isBuff = SetUnsetBuffEffect(skillDataOriginal, Effect, true);
				if (isBuff)
				{
					isBuff = false;

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;//Untested
					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = GetHandle();//My Handle
					skillRes.hAppointedTarget = GetHandle();


					if (pCharSkillReq->hTarget == GetHandle())
					{
						pBuffData.hHandle = GetHandle();
						//pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
						//Handle Buff Time List
						BuffTimeInfo* buff = GetAttributesManager()->GetBuff(pBuffData.tblidx);
						if (buff == NULL)
						{
							BuffTimeInfo newBuff;

							newBuff.BuffID = pBuffData.tblidx;
							newBuff.BuffTime = GetTickCount();
							newBuff.BuffEndTime = pBuffData.dwInitialDuration;
							newBuff.PlayerHandle = pBuffData.hHandle;
							newBuff.BuffIsActive = true;
							newBuff.BuffSlot = 0;
							newBuff.buffInfo = pBuffData;
							newBuff.skillInfo = skillDataOriginal;
							GetAttributesManager()->AddBuff(newBuff);
						}
						else
						{
							buff->buffInfo = pBuffData;
						}
					}
				}
			}

			if (sSkil.wResultCode == GAME_SUCCESS)
			{
				GetPcProfile()->wCurEP -= skillDataOriginal->wRequire_EP;
				UpdateEP(GetPcProfile()->wCurEP);
			}

			SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
			SendPacket((char*)&skillRes, sizeof(sGU_CHAR_ACTION_SKILL));
			SendToPlayerList((char*)&skillRes, sizeof(sGU_CHAR_ACTION_SKILL));
			DelayTime = GetTickCount();
			if (pBuffData.hHandle != 0 && bleed == false || pBuffData.hHandle != INVALID_TBLIDX && bleed == false)
			{
				SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
				SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
			}

			if (GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId == eASPECTSTATE::ASPECTSTATE_SPINNING_ATTACK
				|| GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId == eASPECTSTATE::ASPECTSTATE_BALL)
			{
				UpdateAspectState(GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId);
			}

			GetState()->sCharStateDetail.sCharStateSkillAffecting.skillId = skillDataOriginal->tblidx;
			GetState()->sCharStateDetail.sCharStateSkillAffecting.hTarget = GetHandle();
			UpdateState(eCHARSTATE::CHARSTATE_SKILL_AFFECTING);
		}
		else
		{
			sSkil.wResultCode = ResultCodes::GAME_CHAR_IS_WRONG_STATE;
			SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
		}
	}
	else
	{
		sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;
		SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
	}
}
