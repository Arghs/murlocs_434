

/*

Healing_Stream_Totem.sql

�������� ������ �� �� - �������� ������� �� ����� http://www.wowhead.com/?spell=52042 �� ��� -> ���������� ����� ���

*/


DELETE FROM `spell_bonus_data` WHERE `entry`='52042';


/*

�����:

INSERT INTO spell_bonus_data
   (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `comments`)
VALUES
   (52042, 0.045, 0, 0, 'Shaman - Healing Stream Totem Triggered Heal');

*/


#EoF
