-- mysql -uroot -p123
-- use [database]; // 需要先选择一个数据库
-- source /data_hdd/myfile/mysql_test/daoru.sql     // 导入表

select * from user_profile;
select device_id,gender,age,university  from user_profile;

select distinct(university) from user_profile;
select device_id from user_profile limit 2;
select device_id as user_infos_example from user_profile limit 2;

select device_id,age from user_profile order by age asc;
select device_id,gpa,age from user_profile order by gpa asc, age asc;
select device_id,gpa,age from user_profile order by gpa desc, age desc;


select device_id,university from user_profile where university = "北京大学";
select device_id,gender,age,university from user_profile where age > 24 ;
select device_id,gender,age from user_profile where age >= 20 and age <= 23;
select device_id,gender,age,university from user_profile where university != "复旦大学";
select device_id,gender,age,university from user_profile where university NOT IN ("复旦大学");
select device_id,gender,age,university from user_profile where age IS NOT NULL;








