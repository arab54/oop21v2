#pragma once

#include <string>
#include <cassert>
#include "Container.h"

class Object {
public:
	Object() {
		sm_objectNum++;
	}

	Object(const Object& object) {
		sm_objectNum++;
	}

	virtual ~Object() {
		sm_objectNum--;
	}

	virtual std::string toString() = 0;

	static int getObjectNum() {
		return sm_objectNum;
	}

private:
	static int sm_objectNum;
};


class Task : public virtual Object {
public:
	Task() : m_result("") {}

	virtual void execute() = 0;

	std::string toString() {
		return m_result;
	}
protected:
	std::string m_result;
};


class Named : public virtual Object {
public:
	Named(const std::string &name) : m_name(name) {}

	std::string toString() {
		return "my name is " + m_name;
	}

protected:
	std::string m_name;
};


class ArithmeticTask : public virtual Task, public virtual Named {
public:
	enum class Op { Add, Sub, Mul, Div };

	ArithmeticTask(Op& op, int arg1, int arg2, const std::string& name) :
		Task(), Named(name), m_op(op), m_arg1(arg1), m_arg2(arg2) {}

	void execute() {
		switch (m_op) {
		case Op::Add:
			m_result = std::to_string(m_arg1) + " + " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 + m_arg2);
			break;
		case Op::Sub:
			m_result = std::to_string(m_arg1) + " - " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 - m_arg2);
			break;
		case Op::Mul:
			m_result = std::to_string(m_arg1) + " * " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 * m_arg2);
			break;
		case Op::Div:
			m_result = std::to_string(m_arg1) + " / " + std::to_string(m_arg2) + " = " + std::to_string(m_arg1 / m_arg2);
			break;
		default:
			throw std::logic_error("Unknown binary arithmeric operation ");
		}
	}

	std::string toString() {
		return Named::toString() + ": " + Task::toString();
	}

private:
	Op m_op;
	int m_arg1;
	int m_arg2;
};


class AddTask : public virtual Task {
public:
	AddTask(Container<Task*>& container, Task& task) :
		m_container(container),
		m_task(task) {}

	void execute() {
		m_container.addLast(&m_task);
	}

private:
	Container<Task*>& m_container;
	Task& m_task;
};

class SizeTask : public virtual Task {
public:
	SizeTask(Container<Object*>& container) :
		m_container(container) {}

	void execute() {
		m_result = "Num of objects in container: " + std::to_string(m_container.getSize());
	}

private:
	Container<Object*>& m_container;
};


class CleanTask : public virtual Task {
public:
	CleanTask(Container<Object*>& container) :
		m_container(container) {}

	void execute() {
		m_container.clear();
	}

private:
	Container<Object*>& m_container;
};


class ObjectCountTask : public virtual Task {
public:
	~ObjectCountTask() {}

	void execute() {
		m_result = "Object count: " + std::to_string(Object::getObjectNum());
	}
};
