DELETE FROM `gameobject_loot_template` WHERE `item` = 36908 AND `entry` IN (189973, 190172, 190171, 191303, 190169, 191019, 190170);
-- ���� � �������
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
(189973, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � ��������
(190172, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � ���������
(190171, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � ������
(191303, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � �������� �����
(190169, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � ���� ������
(191019, 36908, 5, 0, 1, 1, 0, 0, 0),
-- ���� � ���� ��������
(190170, 36908, 5, 0, 1, 1, 0, 0, 0);