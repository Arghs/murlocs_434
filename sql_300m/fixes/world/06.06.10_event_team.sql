#http://300murlocs.com/community/index.php/topic/20599-

#���������
UPDATE `item_template` SET `stat_type1` = 7, `stat_value1` = 100, `spellid_1` = 23451 WHERE `entry` = 6143;

#���������� ������� (id 70002) (Spell Effect 30424)
DELETE FROM `gameobject_template` WHERE `entry` = 70002; 
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `size`, `data0`) VALUES ('70002', '22', '8520', '��� 2: ���������� �������', '1.5', '30424');