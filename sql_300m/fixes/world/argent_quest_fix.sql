-- ����������� ������� - ����������, ������ �����������
UPDATE `creature_template` SET `faction_A` = '7', `faction_H` = '7' WHERE `entry` = '30675';
-- ������� �� ���� ���, ������
UPDATE `quest_template` SET `ReqCreatureOrGOId1` = '30675' WHERE `entry` in ('13699', '13713', '13723', '13724', '13725', '13726', '13727', '13728', '13729', '13731');
-- ������������ "Aspirant's Challenge"
UPDATE `quest_template` SET `ReqCreatureOrGOId1` = '33448' WHERE `entry` IN ('13679');