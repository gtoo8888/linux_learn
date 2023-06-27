-- mysql -uroot -p123
-- use [database]; // 需要先选择一个数据库
-- source /data_hdd/myfile/mysql_test/daoru.sql     // 导入表


drop table if exists user_profile;
CREATE TABLE `user_profile` (
`id` int NOT NULL,
`device_id` int NOT NULL,
`gender` varchar(14) NOT NULL,
`age` int ,
`university` varchar(32) NOT NULL,
`gpa` float);
INSERT INTO user_profile VALUES(1,2138,'male',21,'北京大学',3.4);
INSERT INTO user_profile VALUES(2,3214,'male',23,'复旦大学',4.0);
INSERT INTO user_profile VALUES(3,6543,'female',20,'北京大学',3.2);
INSERT INTO user_profile VALUES(4,2315,'female',23,'浙江大学',3.6);
INSERT INTO user_profile VALUES(5,5432,'male',25,'山东大学',3.8);
INSERT INTO user_profile VALUES(6,2131,'male',28,'北京师范大学',3.3);
