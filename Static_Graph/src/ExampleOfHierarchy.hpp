#pragma once
#include "HierarchyToGraphConverter.hpp"
class Aggregated {
private: 
	int _age;
	const char* _name;

public:
	Aggregated(int age, const char* name) :
		_age(age), _name(name){}

	int age() const{
		return _age;
	}

	const char* name() const {
		return _name;
	}
};

class Aggregator {
private:
	Aggregated& _aggregated;

public:
	explicit Aggregator(Aggregated& aggregated):
		_aggregated(aggregated) {}


	int age() const {
		return _aggregated.age();
	}

	const char* name() const {
		return _aggregated.name();
	}
};


using Converter1 = HierarchyToGraphConverter<
	AdjacencyEntry<Aggregated, List<>>,
	AdjacencyEntry<Aggregator, List<Aggregated>>
>;

class Aggregated1 {
private:
	Aggregated& _aggregated;
};
class Aggregator1 {
private:
	Aggregator& _aggregated;
};
class Aggregator2 {
private:
	Aggregator1& _aggregated_aggregator1;
	Aggregated& _aggregated;
};
class Aggregator3 {
private:
	Aggregated1& _aggregated;
};

using Converter2 = HierarchyToGraphConverter<
	AdjacencyEntry<Aggregated, List<Aggregator3>>,
	AdjacencyEntry<Aggregator, List<Aggregated, Aggregator2>>,
	AdjacencyEntry<Aggregator1, List<Aggregator>>,
	AdjacencyEntry<Aggregator2, List<Aggregator1, Aggregated>>,
	AdjacencyEntry<Aggregated1, List<Aggregated>>,
	AdjacencyEntry<Aggregator3, List<Aggregated1>>
>;


class Room {
public:
	std::string roomNumber;
	int capacity;
};

class Device {
public:
	std::string type;
	std::string serialNumber;
};

class Office {
public:
	std::string address;
	std::vector<std::shared_ptr<Room>> rooms;
	std::vector<std::shared_ptr<Device>> devices;

	void addRoom(std::shared_ptr<Room> r);
	void addDevice(std::shared_ptr<Device> d);
};

class Vehicle {
public:
	std::string plateNumber;
	std::string model;
};

class Driver {
public:
	std::string name;
	std::string licenseNumber;
};

class Route {
public:
	std::string from;
	std::string to;
	double distanceKm;
};

class Logistics{
public:
	std::vector<std::shared_ptr<Vehicle>> vehicles;
	std::vector<std::shared_ptr<Driver>> drivers;
	std::vector<std::shared_ptr<Route>> routes;

	void assignRoute(std::shared_ptr<Driver> d, std::shared_ptr<Route> r);
};

class Deadline {
public:
	std::string dueDate; // ISO format: "YYYY-MM-DD"
};

class Budget {
public:
	double total;
	double spent;
};

enum class Status {
	NotStarted,
	InProgress,
	Completed,
	Blocked
};

class Assignee {
public:
	std::string name;
	int employeeId;
};

class Task {
public:
	std::string title;
	std::shared_ptr<Assignee> assignee;
	Status status;
};


class Employee {
public:
	std::string name;
	int id;
	std::string position;
};

class Team {
public:
	std::string name;
	std::vector<std::shared_ptr<Employee>> members;

	void addMember(std::shared_ptr<Employee> e);
};

class Project {
public:
	std::string code;
	std::vector<std::shared_ptr<Task>> tasks;
	std::shared_ptr<Deadline> deadline;
	std::shared_ptr<Budget> budget;

	void addTask(std::shared_ptr<Task> t);
};

class Department {
public:
	std::string name;
	std::vector<std::shared_ptr<Team>> teams;
	std::vector<std::shared_ptr<Project>> projects;

	void addTeam(std::shared_ptr<Team> team);
	void addProject(std::shared_ptr<Project> proj);
};

class Company {
public:
	std::string name;
	std::vector<std::shared_ptr<Department>> departments;
	std::vector<std::shared_ptr<Office>> offices;
	std::shared_ptr<Logistics> logistics;

	void addDepartment(std::shared_ptr<Department> dept);
	void addOffice(std::shared_ptr<Office> office);
};

using Converter3 = HierarchyToGraphConverter<

	// Головні вузли з агрегаціями
	AdjacencyEntry<Company, List<Department, Office, Logistics>>,
	AdjacencyEntry<Department, List<Team, Project>>,
	AdjacencyEntry<Office, List<Room, Device>>,
	AdjacencyEntry<Logistics, List<Vehicle, Driver, Route>>,
	AdjacencyEntry<Project, List<Task, Budget, Deadline>>,
	AdjacencyEntry<Team, List<Employee>>,
	AdjacencyEntry<Task, List<Assignee, Status>>,

	// Вузли без агрегацій (листя)
	AdjacencyEntry<Room, List<>>,
	AdjacencyEntry<Device, List<>>,
	AdjacencyEntry<Driver, List<>>,
	AdjacencyEntry<Vehicle, List<>>,
	AdjacencyEntry<Route, List<>>,
	AdjacencyEntry<Employee, List<>>,
	AdjacencyEntry<Assignee, List<>>,
	AdjacencyEntry<Status, List<>>,
	AdjacencyEntry<Budget, List<>>,
	AdjacencyEntry<Deadline, List<>>

> ; 
using Converter4 = HierarchyToGraphConverter<

	// Головні вузли з агрегаціями
	AdjacencyEntry<Company, List<Department, Office, Logistics>>,
	AdjacencyEntry<Department, List<Team, Project>>,
	AdjacencyEntry<Office, List<Room, Device>>,
	AdjacencyEntry<Logistics, List<Vehicle, Driver, Route>>,
	AdjacencyEntry<Project, List<Task, Budget, Deadline>>,
	AdjacencyEntry<Team, List<Employee>>,
	AdjacencyEntry<Task, List<Assignee, Status>>,

	// Вузли без агрегацій (листя)
	AdjacencyEntry<Room, List<>>,
	AdjacencyEntry<Device, List<>>,
	AdjacencyEntry<Driver, List<>>,
	AdjacencyEntry<Vehicle, List<>>,
	AdjacencyEntry<Route, List<Company>>,
	AdjacencyEntry<Employee, List<>>,
	AdjacencyEntry<Assignee, List<Department>>,
	AdjacencyEntry<Status, List<>>,
	AdjacencyEntry<Budget, List<>>,
	AdjacencyEntry<Deadline, List<>>

> ;

#define DEFINE_CLASS(N) struct Class##N {};

DEFINE_CLASS(0)
DEFINE_CLASS(1)
DEFINE_CLASS(2)
DEFINE_CLASS(3)
DEFINE_CLASS(4)
DEFINE_CLASS(5)
DEFINE_CLASS(6)
DEFINE_CLASS(7)
DEFINE_CLASS(8)
DEFINE_CLASS(9)
DEFINE_CLASS(10)
DEFINE_CLASS(11)
DEFINE_CLASS(12)
DEFINE_CLASS(13)
DEFINE_CLASS(14)
DEFINE_CLASS(15)
DEFINE_CLASS(16)
DEFINE_CLASS(17)
DEFINE_CLASS(18)
DEFINE_CLASS(19)
DEFINE_CLASS(20)
DEFINE_CLASS(21)
DEFINE_CLASS(22)
DEFINE_CLASS(23)
DEFINE_CLASS(24)
DEFINE_CLASS(25)
DEFINE_CLASS(26)
DEFINE_CLASS(27)
DEFINE_CLASS(28)
DEFINE_CLASS(29)
DEFINE_CLASS(30)
DEFINE_CLASS(31)
DEFINE_CLASS(32)
DEFINE_CLASS(33)
DEFINE_CLASS(34)
DEFINE_CLASS(35)
DEFINE_CLASS(36)
DEFINE_CLASS(37)
DEFINE_CLASS(38)
DEFINE_CLASS(39)
DEFINE_CLASS(40)
DEFINE_CLASS(41)
DEFINE_CLASS(42)
DEFINE_CLASS(43)
DEFINE_CLASS(44)
DEFINE_CLASS(45)
DEFINE_CLASS(46)
DEFINE_CLASS(47)
DEFINE_CLASS(48)
DEFINE_CLASS(49)
DEFINE_CLASS(50)
DEFINE_CLASS(51)
DEFINE_CLASS(52)
DEFINE_CLASS(53)
DEFINE_CLASS(54)
DEFINE_CLASS(55)
DEFINE_CLASS(56)
DEFINE_CLASS(57)
DEFINE_CLASS(58)
DEFINE_CLASS(59)
DEFINE_CLASS(60)
DEFINE_CLASS(61)
DEFINE_CLASS(62)
DEFINE_CLASS(63)
DEFINE_CLASS(64)
DEFINE_CLASS(65)
DEFINE_CLASS(66)
DEFINE_CLASS(67)
DEFINE_CLASS(68)
DEFINE_CLASS(69)
DEFINE_CLASS(70)
DEFINE_CLASS(71)
DEFINE_CLASS(72)
DEFINE_CLASS(73)
DEFINE_CLASS(74)
DEFINE_CLASS(75)
DEFINE_CLASS(76)
DEFINE_CLASS(77)
DEFINE_CLASS(78)
DEFINE_CLASS(79)
DEFINE_CLASS(80)
DEFINE_CLASS(81)
DEFINE_CLASS(82)
DEFINE_CLASS(83)
DEFINE_CLASS(84)
DEFINE_CLASS(85)
DEFINE_CLASS(86)
DEFINE_CLASS(87)
DEFINE_CLASS(88)
DEFINE_CLASS(89)
DEFINE_CLASS(90)
DEFINE_CLASS(91)
DEFINE_CLASS(92)
DEFINE_CLASS(93)
DEFINE_CLASS(94)
DEFINE_CLASS(95)
DEFINE_CLASS(96)
DEFINE_CLASS(97)
DEFINE_CLASS(98)
DEFINE_CLASS(99)
DEFINE_CLASS(100)
DEFINE_CLASS(101)
DEFINE_CLASS(102)
DEFINE_CLASS(103)
DEFINE_CLASS(104)
DEFINE_CLASS(105)
DEFINE_CLASS(106)
DEFINE_CLASS(107)
DEFINE_CLASS(108)
DEFINE_CLASS(109)
DEFINE_CLASS(110)
DEFINE_CLASS(111)
DEFINE_CLASS(112)
DEFINE_CLASS(113)
DEFINE_CLASS(114)
DEFINE_CLASS(115)
DEFINE_CLASS(116)
DEFINE_CLASS(117)
DEFINE_CLASS(118)
DEFINE_CLASS(119)
DEFINE_CLASS(120)
DEFINE_CLASS(121)
DEFINE_CLASS(122)
DEFINE_CLASS(123)
DEFINE_CLASS(124)
DEFINE_CLASS(125)
DEFINE_CLASS(126)
DEFINE_CLASS(127)
DEFINE_CLASS(128)
DEFINE_CLASS(129)
DEFINE_CLASS(130)
DEFINE_CLASS(131)
DEFINE_CLASS(132)
DEFINE_CLASS(133)
DEFINE_CLASS(134)
DEFINE_CLASS(135)
DEFINE_CLASS(136)
DEFINE_CLASS(137)
DEFINE_CLASS(138)
DEFINE_CLASS(139)
DEFINE_CLASS(140)
DEFINE_CLASS(141)
DEFINE_CLASS(142)
DEFINE_CLASS(143)
DEFINE_CLASS(144)
DEFINE_CLASS(145)
DEFINE_CLASS(146)
DEFINE_CLASS(147)
DEFINE_CLASS(148)
DEFINE_CLASS(149)
DEFINE_CLASS(150)
DEFINE_CLASS(151)
DEFINE_CLASS(152)
DEFINE_CLASS(153)
DEFINE_CLASS(154)
DEFINE_CLASS(155)
DEFINE_CLASS(156)
DEFINE_CLASS(157)
DEFINE_CLASS(158)
DEFINE_CLASS(159)
DEFINE_CLASS(160)
DEFINE_CLASS(161)
DEFINE_CLASS(162)
DEFINE_CLASS(163)
DEFINE_CLASS(164)
DEFINE_CLASS(165)
DEFINE_CLASS(166)
DEFINE_CLASS(167)
DEFINE_CLASS(168)
DEFINE_CLASS(169)
DEFINE_CLASS(170)
DEFINE_CLASS(171)
DEFINE_CLASS(172)
DEFINE_CLASS(173)
DEFINE_CLASS(174)
DEFINE_CLASS(175)
DEFINE_CLASS(176)
DEFINE_CLASS(177)
DEFINE_CLASS(178)
DEFINE_CLASS(179)
DEFINE_CLASS(180)
DEFINE_CLASS(181)
DEFINE_CLASS(182)
DEFINE_CLASS(183)
DEFINE_CLASS(184)
DEFINE_CLASS(185)
DEFINE_CLASS(186)
DEFINE_CLASS(187)
DEFINE_CLASS(188)
DEFINE_CLASS(189)
DEFINE_CLASS(190)
DEFINE_CLASS(191)
DEFINE_CLASS(192)
DEFINE_CLASS(193)
DEFINE_CLASS(194)
DEFINE_CLASS(195)
DEFINE_CLASS(196)
DEFINE_CLASS(197)
DEFINE_CLASS(198)
DEFINE_CLASS(199)

// === Агрегації ===
using Converter5 = HierarchyToGraphConverter <
    AdjacencyEntry<Class10, List<Class7, Class8, Class9>>,
    AdjacencyEntry<Class11, List<Class10, Class8, Class9>>,
    AdjacencyEntry<Class12, List<Class10, Class11, Class9>>,
    AdjacencyEntry<Class13, List<Class10, Class11, Class12>>,
    AdjacencyEntry<Class14, List<Class11, Class12, Class13>>,
    AdjacencyEntry<Class15, List<Class12, Class13, Class14>>,
    AdjacencyEntry<Class16, List<Class13, Class14, Class15>>,
    AdjacencyEntry<Class17, List<Class130, Class14, Class15, Class16>>,
    AdjacencyEntry<Class18, List<Class15, Class16, Class17>>,
    AdjacencyEntry<Class19, List<Class16, Class17, Class18>>,
    AdjacencyEntry<Class20, List<Class17, Class18, Class19>>,
    AdjacencyEntry<Class21, List<Class18, Class19, Class20>>,
    AdjacencyEntry<Class22, List<Class19, Class20, Class21>>,
    AdjacencyEntry<Class23, List<Class20, Class21, Class22>>,
    AdjacencyEntry<Class24, List<Class21, Class22, Class23>>,
    AdjacencyEntry<Class25, List<Class22, Class23, Class24>>,
    AdjacencyEntry<Class26, List<Class23, Class24, Class25>>,
    AdjacencyEntry<Class27, List<Class24, Class25, Class26>>,
    AdjacencyEntry<Class28, List<Class25, Class26, Class27>>,
    AdjacencyEntry<Class29, List<Class26, Class27, Class28>>,
    AdjacencyEntry<Class30, List<Class27, Class28, Class29>>,
    AdjacencyEntry<Class31, List<Class28, Class29, Class30, Class51>>,
    AdjacencyEntry<Class32, List<Class29, Class30, Class31>>,
    AdjacencyEntry<Class33, List<Class30, Class31, Class32>>,
    AdjacencyEntry<Class34, List<Class31, Class32, Class33>>,
    AdjacencyEntry<Class35, List<Class32, Class33, Class34>>,
    AdjacencyEntry<Class36, List<Class129, Class33, Class34, Class35>>,
    AdjacencyEntry<Class37, List<Class34, Class35, Class36>>,
    AdjacencyEntry<Class38, List<Class35, Class36, Class37>>,
    AdjacencyEntry<Class39, List<Class193, Class36, Class37, Class38>>,
    AdjacencyEntry<Class40, List<Class36, Class37, Class38, Class39>>,
    AdjacencyEntry<Class41, List<Class38, Class39, Class40, Class98>>,
    AdjacencyEntry<Class42, List<Class39, Class40, Class41>>,
    AdjacencyEntry<Class43, List<Class40, Class41, Class42>>,
    AdjacencyEntry<Class44, List<Class41, Class42, Class43>>,
    AdjacencyEntry<Class45, List<Class42, Class43, Class44>>,
    AdjacencyEntry<Class46, List<Class43, Class44, Class45>>,
    AdjacencyEntry<Class47, List<Class44, Class45, Class46>>,
    AdjacencyEntry<Class48, List<Class45, Class46, Class47>>,
    AdjacencyEntry<Class49, List<Class46, Class47, Class48, Class86>>,
    AdjacencyEntry<Class50, List<Class47, Class48, Class49, Class91>>,
    AdjacencyEntry<Class51, List<Class31, Class48, Class49, Class50>>,
    AdjacencyEntry<Class52, List<Class49, Class50, Class51>>,
    AdjacencyEntry<Class53, List<Class50, Class51, Class52>>,
    AdjacencyEntry<Class54, List<Class51, Class52, Class53>>,
    AdjacencyEntry<Class55, List<Class52, Class53, Class54>>,
    AdjacencyEntry<Class56, List<Class53, Class54, Class55>>,
    AdjacencyEntry<Class57, List<Class54, Class55, Class56>>,
    AdjacencyEntry<Class58, List<Class55, Class56, Class57>>,
    AdjacencyEntry<Class59, List<Class56, Class57, Class58>>,
    AdjacencyEntry<Class60, List<Class57, Class58, Class59, Class62>>,
    AdjacencyEntry<Class61, List<Class17, Class58, Class59, Class60>>,
    AdjacencyEntry<Class62, List<Class127, Class59, Class60, Class61>>,
    AdjacencyEntry<Class63, List<Class60, Class61, Class62>>,
    AdjacencyEntry<Class64, List<Class61, Class62, Class63>>,
    AdjacencyEntry<Class65, List<Class62, Class63, Class64>>,
    AdjacencyEntry<Class66, List<Class63, Class64, Class65>>,
    AdjacencyEntry<Class67, List<Class64, Class65, Class66>>,
    AdjacencyEntry<Class68, List<Class65, Class66, Class67>>,
    AdjacencyEntry<Class69, List<Class66, Class67, Class68>>,
    AdjacencyEntry<Class70, List<Class67, Class68, Class69>>,
    AdjacencyEntry<Class71, List<Class68, Class69, Class70>>,
    AdjacencyEntry<Class72, List<Class69, Class70, Class71>>,
    AdjacencyEntry<Class73, List<Class70, Class71, Class72>>,
    AdjacencyEntry<Class74, List<Class71, Class72, Class73>>,
    AdjacencyEntry<Class75, List<Class72, Class73, Class74>>,
    AdjacencyEntry<Class76, List<Class103, Class73, Class74, Class75>>,
    AdjacencyEntry<Class77, List<Class74, Class75, Class76>>,
    AdjacencyEntry<Class78, List<Class75, Class76, Class77>>,
    AdjacencyEntry<Class79, List<Class76, Class77, Class78>>,
    AdjacencyEntry<Class80, List<Class77, Class78, Class79>>,
    AdjacencyEntry<Class81, List<Class78, Class79, Class80>>,
    AdjacencyEntry<Class82, List<Class130, Class79, Class80, Class81>>,
    AdjacencyEntry<Class83, List<Class80, Class81, Class82>>,
    AdjacencyEntry<Class84, List<Class81, Class82, Class83>>,
    AdjacencyEntry<Class85, List<Class82, Class83, Class84>>,
    AdjacencyEntry<Class86, List<Class49, Class83, Class84, Class85>>,
    AdjacencyEntry<Class87, List<Class84, Class85, Class86>>,
    AdjacencyEntry<Class88, List<Class85, Class86, Class87>>,
    AdjacencyEntry<Class89, List<Class86, Class87, Class88>>,
    AdjacencyEntry<Class90, List<Class151, Class87, Class88, Class89>>,
    AdjacencyEntry<Class91, List<Class50, Class88, Class89, Class90>>,
    AdjacencyEntry<Class92, List<Class89, Class90, Class91>>,
    AdjacencyEntry<Class93, List<Class90, Class91, Class92, Class94>>,
    AdjacencyEntry<Class94, List<Class91, Class92, Class93>>,
    AdjacencyEntry<Class95, List<Class92, Class93, Class94>>,
    AdjacencyEntry<Class96, List<Class93, Class94, Class95>>,
    AdjacencyEntry<Class97, List<Class94, Class95, Class96>>,
    AdjacencyEntry<Class98, List<Class130, Class147, Class95, Class96, Class97>>,
    AdjacencyEntry<Class99, List<Class96, Class97, Class98>>,
    AdjacencyEntry<Class100, List<Class97, Class98, Class99>>,
    AdjacencyEntry<Class101, List<Class100, Class178, Class98, Class99>>,
    AdjacencyEntry<Class102, List<Class100, Class101, Class99>>,
    AdjacencyEntry<Class103, List<Class100, Class101, Class102, Class76>>,
    AdjacencyEntry<Class104, List<Class101, Class102, Class103, Class152>>,
    AdjacencyEntry<Class105, List<Class102, Class103, Class104>>,
    AdjacencyEntry<Class106, List<Class103, Class104, Class105>>,
    AdjacencyEntry<Class107, List<Class104, Class105, Class106>>,
    AdjacencyEntry<Class108, List<Class105, Class106, Class107>>,
    AdjacencyEntry<Class109, List<Class106, Class107, Class108>>,
    AdjacencyEntry<Class110, List<Class107, Class108, Class109>>,
    AdjacencyEntry<Class111, List<Class108, Class109, Class110>>,
    AdjacencyEntry<Class112, List<Class109, Class110, Class111>>,
    AdjacencyEntry<Class113, List<Class110, Class111, Class112>>,
    AdjacencyEntry<Class114, List<Class111, Class112, Class113>>,
    AdjacencyEntry<Class115, List<Class112, Class113, Class114>>,
    AdjacencyEntry<Class116, List<Class113, Class114, Class115>>,
    AdjacencyEntry<Class117, List<Class114, Class115, Class116>>,
    AdjacencyEntry<Class118, List<Class115, Class116, Class117>>,
    AdjacencyEntry<Class119, List<Class116, Class117, Class118>>,
    AdjacencyEntry<Class120, List<Class117, Class118, Class119>>,
    AdjacencyEntry<Class121, List<Class118, Class119, Class120>>,
    AdjacencyEntry<Class122, List<Class119, Class120, Class121>>,
    AdjacencyEntry<Class123, List<Class120, Class121, Class122>>,
    AdjacencyEntry<Class124, List<Class121, Class122, Class123>>,
    AdjacencyEntry<Class125, List<Class122, Class123, Class124>>,
    AdjacencyEntry<Class126, List<Class123, Class124, Class125>>,
    AdjacencyEntry<Class127, List<Class124, Class125, Class126, Class60>>,
    AdjacencyEntry<Class128, List<Class125, Class126, Class127>>,
    AdjacencyEntry<Class129, List<Class126, Class127, Class128, Class40>>,
    AdjacencyEntry<Class130, List<Class127, Class128, Class129, Class41, Class61, Class82>>,
    AdjacencyEntry<Class131, List<Class128, Class129, Class130>>,
    AdjacencyEntry<Class132, List<Class129, Class130, Class131>>,
    AdjacencyEntry<Class133, List<Class130, Class131, Class132>>,
    AdjacencyEntry<Class134, List<Class131, Class132, Class133>>,
    AdjacencyEntry<Class135, List<Class132, Class133, Class134>>,
    AdjacencyEntry<Class136, List<Class133, Class134, Class135>>,
    AdjacencyEntry<Class137, List<Class134, Class135, Class136>>,
    AdjacencyEntry<Class138, List<Class135, Class136, Class137>>,
    AdjacencyEntry<Class139, List<Class136, Class137, Class138>>,
    AdjacencyEntry<Class140, List<Class137, Class138, Class139>>,
    AdjacencyEntry<Class141, List<Class138, Class139, Class140>>,
    AdjacencyEntry<Class142, List<Class139, Class140, Class141>>,
    AdjacencyEntry<Class143, List<Class140, Class141, Class142>>,
    AdjacencyEntry<Class144, List<Class141, Class142, Class143, Class90>>,
    AdjacencyEntry<Class145, List<Class142, Class143, Class144>>,
    AdjacencyEntry<Class146, List<Class143, Class144, Class145>>,
    AdjacencyEntry<Class147, List<Class144, Class145, Class146, Class98>>,
    AdjacencyEntry<Class148, List<Class145, Class146, Class147>>,
    AdjacencyEntry<Class149, List<Class146, Class147, Class148>>,
    AdjacencyEntry<Class150, List<Class147, Class148, Class149>>,
    AdjacencyEntry<Class151, List<Class144, Class148, Class149, Class150>>,
    AdjacencyEntry<Class152, List<Class149, Class150, Class151, Class176>>,
    AdjacencyEntry<Class153, List<Class150, Class151, Class152>>,
    AdjacencyEntry<Class154, List<Class151, Class152, Class153>>,
    AdjacencyEntry<Class155, List<Class152, Class153, Class154>>,
    AdjacencyEntry<Class156, List<Class153, Class154, Class155>>,
    AdjacencyEntry<Class157, List<Class154, Class155, Class156>>,
    AdjacencyEntry<Class158, List<Class155, Class156, Class157>>,
    AdjacencyEntry<Class159, List<Class156, Class157, Class158>>,
    AdjacencyEntry<Class160, List<Class157, Class158, Class159>>,
    AdjacencyEntry<Class161, List<Class158, Class159, Class160>>,
    AdjacencyEntry<Class162, List<Class159, Class160, Class161>>,
    AdjacencyEntry<Class163, List<Class160, Class161, Class162>>,
    AdjacencyEntry<Class164, List<Class161, Class162, Class163>>,
    AdjacencyEntry<Class165, List<Class162, Class163, Class164>>,
    AdjacencyEntry<Class166, List<Class163, Class164, Class165>>,
    AdjacencyEntry<Class167, List<Class164, Class165, Class166>>,
    AdjacencyEntry<Class168, List<Class165, Class166, Class167>>,
    AdjacencyEntry<Class169, List<Class166, Class167, Class168>>,
    AdjacencyEntry<Class170, List<Class167, Class168, Class169>>,
    AdjacencyEntry<Class171, List<Class168, Class169, Class170>>,
    AdjacencyEntry<Class172, List<Class169, Class170, Class171>>,
    AdjacencyEntry<Class173, List<Class170, Class171, Class172>>,
    AdjacencyEntry<Class174, List<Class171, Class172, Class173>>,
    AdjacencyEntry<Class175, List<Class172, Class173, Class174>>,
    AdjacencyEntry<Class176, List<Class104, Class173, Class174, Class175>>,
    AdjacencyEntry<Class177, List<Class174, Class175, Class176>>,
    AdjacencyEntry<Class178, List<Class101, Class175, Class176, Class177>>,
    AdjacencyEntry<Class179, List<Class176, Class177, Class178>>,
    AdjacencyEntry<Class180, List<Class177, Class178, Class179>>,
    AdjacencyEntry<Class181, List<Class178, Class179, Class180>>,
    AdjacencyEntry<Class182, List<Class179, Class180, Class181>>,
    AdjacencyEntry<Class183, List<Class180, Class181, Class182>>,
    AdjacencyEntry<Class184, List<Class181, Class182, Class183>>,
    AdjacencyEntry<Class185, List<Class182, Class183, Class184>>,
    AdjacencyEntry<Class186, List<Class183, Class184, Class185>>,
    AdjacencyEntry<Class187, List<Class184, Class185, Class186>>,
    AdjacencyEntry<Class188, List<Class185, Class186, Class187>>,
    AdjacencyEntry<Class189, List<Class186, Class187, Class188>>,
    AdjacencyEntry<Class190, List<Class187, Class188, Class189>>,
    AdjacencyEntry<Class191, List<Class188, Class189, Class190>>,
    AdjacencyEntry<Class192, List<Class189, Class190, Class191>>,
    AdjacencyEntry<Class193, List<Class190, Class191, Class192, Class39>>,
    AdjacencyEntry<Class194, List<Class191, Class192, Class193>>,
    AdjacencyEntry<Class195, List<Class192, Class193, Class194>>,
    AdjacencyEntry<Class196, List<Class193, Class194, Class195>>,
    AdjacencyEntry<Class197, List<Class194, Class195, Class196>>,
    AdjacencyEntry<Class198, List<Class195, Class196, Class197>>,
    AdjacencyEntry<Class199, List<Class196, Class197, Class198>>
> ;
