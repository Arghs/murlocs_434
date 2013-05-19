/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_queen_azshara
SD%Complete: 0
SDComment: Placeholder
SDCategory: Well of Eternity
EndScriptData */

#include "precompiled.h"
#include "well_of_eternity.h";

enum
{
    EVENT_ACTIVATE_MAGUS    = 1,
};

struct MANGOS_DLL_DECL boss_queen_azsharaAI : public ScriptedAI
{
    boss_queen_azsharaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool started;
    EventMap events;
    GuidSet deadMagus;

    void Reset() override
    {
        for (GuidSet::iterator itr = deadMagus.begin(); itr != deadMagus.end(); ++itr)
            if (Creature* unit = m_creature->GetMap()->GetAnyTypeCreature(*itr))
            {
                unit->Respawn();
                unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        deadMagus.clear();

        started = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        events.Reset();
    }

    void DamageTaken(Unit* who, uint32& damage) override
    {
        damage = 0;
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!started && who->GetDistance2d(m_creature) < 80.0f && m_pInstance->GetData(TYPE_AZSHARA) != DONE)
        {
            started = true;
            m_creature->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_ACTIVATE_MAGUS, 10000);
        }
    }

    void EnterEvadeMode() override
    {
        started = false;
        ScriptedAI::EnterEvadeMode();
    }

    void Aggro(Unit* pWho) override
    {
    }

    void JustDied(Unit* pKiller) override
    {
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type != DATA_MAGUS_DEAD)
            return;

        deadMagus.insert(ObjectGuid(HIGHGUID_UNIT, value));
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!started)
            return;

        events.Update(uiDiff);

        if (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ACTIVATE_MAGUS:
                {
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, m_creature, NPC_ENCHANTED_MAGUS_1, 100.0f);
                    GetCreatureListWithEntryInGrid(creatures, m_creature, NPC_ENCHANTED_MAGUS_2, 100.0f);
                    GetCreatureListWithEntryInGrid(creatures, m_creature, NPC_ENCHANTED_MAGUS_3, 100.0f);

                    Unit* unit = GetClosestAttackableUnit(m_creature, 100.0f);

                    uint8 counter = 0;
                    for (std::list<Creature*>::iterator itr = creatures.begin(); itr != creatures.end() && counter < 2; ++itr)
                    {
                        if ((*itr)->isDead())
                            continue;

                        if (deadMagus.find((*itr)->GetObjectGuid()) != deadMagus.end())
                            continue;

                        ++counter;

                        (*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        (*itr)->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                        if (unit)
                            (*itr)->Attack(unit, false);
                    }

                    if (counter == 0)
                    {
                        m_pInstance->SetData(TYPE_AZSHARA, DONE);
                        EnterEvadeMode();
                    }
                    break;
                }
            }
        }
    }
};

CreatureAI* GetAI_boss_queen_azshara(Creature* pCreature)
{
    return new boss_queen_azsharaAI(pCreature);
}

void AddSC_boss_queen_azshara()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_queen_azshara";
    pNewScript->GetAI = &GetAI_boss_queen_azshara;
    pNewScript->RegisterSelf();
}
