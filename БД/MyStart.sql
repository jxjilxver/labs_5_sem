create table XXX_t(x number(3) primary key, s varchar(50));
insert into XXX_t(x,s) values (1,'one');
insert into XXX_t(x,s) values (2,'two');
insert into XXX_t(x,s) values (3,'three');
commit;
update XXX_t set x=4 where x=1;
update XXX_t set x=5 where x=2;
commit;
select count(*) from XXX_t;
select * from XXX_t where s='three';
delete from XXX_t where x=4;
commit;
create table XXX_t1(y number(3) constraint FK1  references XXX_t(x), f varchar(50));
insert into XXX_t1(y,f) values (1,'four');
insert into XXX_t1(y,f) values (1,'five');
insert into XXX_t1(y,f) values (2,'six');
select * from XXX_t left outer join XXX_t1 on xxx_t.x=xxx_t1.y
select * from XXX_t right outer join XXX_t1 on xxx_t.x=xxx_t1.y
select * from XXX_t inner join XXX_t1 on xxx_t.x=xxx_t1.y
drop table xxx_t
drop table xxx_t1