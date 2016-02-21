// openhomm - open source clone of Heroes of Might and Magic III
// Copyright (C) 2009-2010 openhomm developers team (see AUTHORS)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#pragma once

struct SecondarySkill_t {
    quint8 skillID;
    quint8 skillLevel;
};
QT_BEGIN_NAMESPACE
QDataStream &operator<<(QDataStream &, const SecondarySkill_t &);
QDataStream &operator>>(QDataStream &, SecondarySkill_t &);
QT_END_NAMESPACE

struct hrObject {
    HString filename;
    quint8 passability[6];
    quint8 actions[6];
    quint16 landscape;
    quint16 land_edit_groups; // for editor
    quint32 object_class;
    quint32 object_number;
    quint8 object_group;
    quint8 isOverlay;
    quint8 junk[16]; // need more info
};

struct hrObjectOptions {
    quint8 coord[3]; // x, y, z;
    quint32 objectID;
    quint8 junk[5]; // need more info
};

struct Guard_t {
    quint16 GuardID;
    quint16 GuardCount;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const Guard_t &);
QDataStream &operator>>(QDataStream &, Guard_t &s);
QT_END_NAMESPACE

struct ObjectMessageGuards {
    quint8 hasText;

//if ( isText == 1 ) {
    HString text;
//
//
    quint8 hasGuards;
//
//  if ( isGuards == 1 ) {
        Guard_t guards[7];

    quint8 junk[4];
//    }
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectArtefact &);
QDataStream &operator>>(QDataStream &, ObjectMessageGuards &s);
QT_END_NAMESPACE

struct ObjectDwelling {
    quint32 owner; // FF - nobody
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectDwelling &);
QDataStream &operator>>(QDataStream &, ObjectDwelling &s);
QT_END_NAMESPACE

struct ObjectShipyard {
    quint32 owner; // FF - nobody
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectShipyard &);
QDataStream &operator>>(QDataStream &, ObjectShipyard &s);
QT_END_NAMESPACE

struct ObjectGeneralRandomDwelling {
    quint32 owner;
    quint32 castleScpecID;
//  if (castleScpecID == 0 )
    quint16 towns;

    quint8 minlevel;
    quint8 maxlevel;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectGeneralRandomDwelling &);
QDataStream &operator>>(QDataStream &, ObjectGeneralRandomDwelling &s);
QT_END_NAMESPACE

struct ObjectLevelRandomDwelling {
    quint32 owner;
    quint32 castleScpecID;
//  if ( castleScpecID == 0 )
    quint16 towns;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectLevelRandomDwelling &);
QDataStream &operator>>(QDataStream &, ObjectLevelRandomDwelling &s);
QT_END_NAMESPACE

struct ObjectTownRandomDwelling {
    quint32 owner;
    quint8 minlevel;
    quint8 maxlevel;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectTownRandomDwelling &);
QDataStream &operator>>(QDataStream &, ObjectTownRandomDwelling &s);
QT_END_NAMESPACE

struct ObjectGrail {
    qint32 radius;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectGrail &);
QDataStream &operator>>(QDataStream &, ObjectGrail &s);
QT_END_NAMESPACE

struct Resources_t
{
    qint32 wood;
    qint32 mercury;
    qint32 ore;
    qint32 sulfur;
    qint32 crystal;
    qint32 gem;
    qint32 gold;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const Resources_t &);
QDataStream &operator>>(QDataStream &, Resources_t &s);
QT_END_NAMESPACE

struct ObjectMonster {
    quint32 monsterID;
    quint16 monstersCount; // if 0, then random
    quint8 mood;//character
    quint8 isTreasureOrText;

//  if ( isTreasureOrText == 1 ) {
        HString text;

        Resources_t res;
        quint16 artefactID;
//  }

    quint8 monsterNeverRunAway; // 1 - yes, 0 - no
    quint8 monsterDontGrowUp; // 1 - yes, 0 - no

    quint8 junk2[2];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectMonster &);
QDataStream &operator>>(QDataStream &, ObjectMonster &s);
QT_END_NAMESPACE

struct ObjectPandora {
    ObjectMessageGuards messageGuards;
    quint32 exp;
    qint32 spell_points;
    qint8 morals;
    qint8 luck;

    Resources_t res;

    quint8 offence;
    quint8 defence;
    quint8 power;
    quint8 knowledge;

    quint8 secSkillsCount;

//    if ( isSecSkills > 0 ) {
        QVector<SecondarySkill_t> sec_skills;

    quint8 artefactCount;

//    if ( artefacts > 0 ) {
        QVector<quint16> artefacts;

    quint8 spellsCount;

//    if ( isSpells > 0 ) {
        QVector<quint8> spells;

    quint8 monstreCount;

//    if ( monstres_count > 0 ) {
        QVector<Guard_t> monstres;

    quint8 junk3[8];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectPandora &);
QDataStream &operator>>(QDataStream &, ObjectPandora &s);
QT_END_NAMESPACE

struct ObjectResource {
    ObjectMessageGuards res;
    quint32 quantity;
    quint32 junk;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectResource &);
QDataStream &operator>>(QDataStream &, ObjectResource &s);
QT_END_NAMESPACE

struct ObjectScientist {
    quint8 bonus_type; // FF - Random
    union {//quint8?
        quint32 primaryID;
        quint32 secondaryID;
        quint32 spellID;
    };
    quint8 junk2[3];//6 byte?
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectScientist &);
QDataStream &operator>>(QDataStream &, ObjectScientist &s);
QT_END_NAMESPACE

struct ObjectSpell {
    ObjectMessageGuards spell;
    quint32 spellID;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectSpell &);
QDataStream &operator>>(QDataStream &, ObjectSpell &s);
QT_END_NAMESPACE

struct TownEvent_t {
    HString event_name;
    HString event_text;

    Resources_t res;

    quint8 players_affected;
    quint8 human_affected;
    quint8 ai_affected;

    quint16 day_of_first_event;
    quint16 event_iteration;
    quint32 junk[4];
    quint8 buildings[6];
    quint16 creatures[7];
    quint32 junk2;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const TownEvent_t &);
QDataStream &operator>>(QDataStream &, TownEvent_t &s);
QT_END_NAMESPACE

struct ObjectTown {
    quint32 identifier;
    quint8 owner;

    quint8 hasName;

//    if ( isName == 1 )
        HString name;

    quint8 hasGuard;

//    if (isGuard == 1 )
         Guard_t guards[7];

    quint8 formation; // 00 - standalone, 01 - group

    quint8 hasBuildings;

//    if ( isBuildings == 1 ) {
        quint8 built[6];
        quint8 active[6];
//    } else {
        quint8 hasFort;
//    }

    quint8 mustSpells[9];
    quint8 canSpells[9];

    quint32 eventCount;

//    if ( event_quantity > 0 ) {
        QVector<TownEvent_t> events;
//    }
    quint8 alignment;
    quint8 junk3[3];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectTown &);
QDataStream &operator>>(QDataStream &, ObjectTown &s);
QT_END_NAMESPACE

struct ObjectShrine {
    quint32 spellID;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectShrine &);
QDataStream &operator>>(QDataStream &, ObjectShrine &s);
QT_END_NAMESPACE

struct ObjectEvent {
    ObjectPandora event;
    quint8 players;
    quint8 isAICan;
    quint8 disableAfterFirstDay;
    quint32 junk;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectEvent &);
QDataStream &operator>>(QDataStream &, ObjectEvent &s);
QT_END_NAMESPACE

struct ObjectSign {
    HString text;
    quint32 junk;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectSign &);
QDataStream &operator>>(QDataStream &, ObjectSign &s);

//QDataStream &operator<<(QDataStream &, const hrObject &);
QDataStream &operator>>(QDataStream &, hrObject &s);
//QDataStream &operator<<(QDataStream &, const hrObjectOptions &);
QDataStream &operator>>(QDataStream &, hrObjectOptions &s);
QT_END_NAMESPACE

struct ObjectProphet {//seer hut
    quint8 quest;

    union
    {
        quint32 level; // quest 1
        struct //  quest 2
        {
            quint8 offence, defence, power, knowledge;
        };
        quint32 heroID; // quest 3
        quint8 heroID_; // quest 8
        quint32 monsterID; // quest 4
        quint8 playerColor; // quest 9
    };
    // quest 5
    quint8 artQuantity;
    QVector<quint16> arts;
    // quest 6
    quint8 creaturesQuantity;
    QVector<Guard_t> creatures;

    Resources_t res; // quest 7

    quint32 time_limit; // 0xFFFFFFFF - no limit
    HString quest_begin;
    HString quest_inprocess;
    HString quest_end;

    quint8 reward;

    union
    {
        quint32 exp; // 1
        quint32 spellPoints; // 2
        quint8 morale; // 3
        quint8 lucky; // 4
        struct //5
        {
            quint8 resID;
            quint32 resQ;
        };
        struct //6
        {
            quint8 priSkillID, priSkillBonus;
        };
        struct // 7
        {
            quint8 secSkillID, secSkillLevel;
        };
        quint16 artId; // 8
        quint8 spell; // 9
        struct //10
        {
            quint16 creatureID, creatureQuantity;
        };
    };

    quint16 junk;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectProphet &);
QDataStream &operator>>(QDataStream &, ObjectProphet &s);
QT_END_NAMESPACE

struct ObjectHero {
    quint32 heroID;
    quint8 color;
    quint8 hero; // FF - random

    quint8 isName;

//    if ( isName == 1 )
        HString name;

    quint8 isExp;

//    if ( isExp == 1 )
        quint32 exp;

    quint8 isPortrait;

//    if ( isPortrait == 1)
        quint8 portrait;

    quint8 isSecondary;

//    if ( isSecondary == 1 ) {
         quint32 skills_quantity;
//         if ( skills_quantity > 0 )
             QVector<SecondarySkill_t> skills;

//    }

    quint8 isCreature;
//    if ( isCreature == 1 )
        Guard_t creatures[7];

    quint8 creaturesFormation;

    quint8 isArtefacts;

//    if ( isArtefacts == 1 ) {
        quint16 headID;
        quint16 shouldersID;
        quint16 neckID;
        quint16 rightHandID;
        quint16 leftHandID;
        quint16 trunkID;
        quint16 rightRingID;
        quint16 leftRingID;
        quint16 legsID;
        quint16 misc1ID;
        quint16 misc2ID;
        quint16 misc3ID;
        quint16 misc4ID;
        quint16 machine1ID;
        quint16 machine2ID;
        quint16 machine3ID;
        quint16 machine4ID;
        quint16 magicbook;
        quint16 misc5ID;

        quint16 knapsack_count;

//        if ( knapsack_count > 0 )
        QVector<quint16> knapsack;
//    }
    quint8 zoneRadius;

    quint8 isBiography;

//    if ( isBiography == 1 )
        HString biography;

    quint8 gender;

    quint8 isSpells;
//    if ( isSpells == 1 )
        quint8 spells[9];

    quint8 isPrimary;
//    if ( isPrimary == 1 ) {
        quint8 offence;
        quint8 defence;
        quint8 power;
        quint8 knowledge;
//    }

    quint32 unknown[4];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectHero &);
QDataStream &operator>>(QDataStream &, ObjectHero &s);
QT_END_NAMESPACE

struct ObjectHeroPlaceholder {
    quint8 color;
    quint8 type;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectHeroPlaceholder &);
QDataStream &operator>>(QDataStream &, ObjectHeroPlaceholder &s);
QT_END_NAMESPACE

struct ObjectMine {
    quint32 color;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectMine &);
QDataStream &operator>>(QDataStream &, ObjectMine &s);
QT_END_NAMESPACE

struct ObjectWitchHut {
    quint32 secskills;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectWitchHut &);
QDataStream &operator>>(QDataStream &, ObjectWitchHut &s);
QT_END_NAMESPACE

struct globalEvent {
    HString name;
    HString text;

    Resources_t res;

    quint8 players_affected;
    quint8 human_affected;
    quint8 ai_affected;

    quint16 day_of_first_event;
    quint16 event_iteration;

    quint32 junk[4];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const globalEvent &);
QDataStream &operator>>(QDataStream &, globalEvent &s);
QT_END_NAMESPACE

struct ObjectQuestionGuard {
    quint8 quest;

    union
    {
        quint32 level; // 1
        struct // 2
        {
            quint8 offence, defence, power, knowledge;
        };
        quint32 heroID; // 3
        quint8 heroID_; // 8
        quint32 monsterID; // 4
        quint8 playerColor; // 9
    };
    // quest 5
    quint8 artQuantity;
    QVector<quint16> arts;
    // quest 6
    quint8 creaturesQuantity;
    QVector<Guard_t> creatures;

    Resources_t res; // quest 7

    quint32 time_limit; // FF FF FF FF - no limit
    HString quest_begin;
    HString quest_inprocess;
    HString quest_end;
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectQuestionGuard &);
QDataStream &operator>>(QDataStream &, ObjectQuestionGuard &s);
QT_END_NAMESPACE

struct ObjectGarrison {
    quint32 color;
    Guard_t guards[7];
    quint8 undeleteSoldiers;
    quint32 junk[2];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectGarrison &);
QDataStream &operator>>(QDataStream &, ObjectGarrison &s);
QT_END_NAMESPACE

struct ObjectAbandonedMine {
    quint8 resources;
    quint8 junk[3];
};
QT_BEGIN_NAMESPACE
//QDataStream &operator<<(QDataStream &, const ObjectAbandonedMine &);
QDataStream &operator>>(QDataStream &, ObjectAbandonedMine &s);
QT_END_NAMESPACE
