#pragma once

#include "Container.h"
#include "Objects.h"

class TaskFactory {
public:
    TaskFactory() {
        m_taskContainers = Container<Container<Task*>*>();
        m_objectContainers = Container<Container<Object*>*>();
        m_tasks = Container<Task*>();
    }

    ~TaskFactory() {
        m_tasks.resetIterator();
        while (m_tasks.hasNext()) {
            Task* task = m_tasks.getNext();
            delete task;
        }

        m_taskContainers.resetIterator();
        while (m_taskContainers.hasNext()) {
            Container<Task*>* tasks = m_taskContainers.getNext();
            delete tasks;
        }

        m_objectContainers.resetIterator();
        while (m_objectContainers.hasNext()) {
            Container<Object*>* objects = m_objectContainers.getNext();
            delete objects;
        }
    }

    
    ArithmeticTask* createArithmeticTask() {
        ArithmeticTask::Op op = ArithmeticTask::Op(getRandomInt() % 4);
        int arg1 = getRandomInt();
        int arg2 = getRandomInt();
        std::string name = "a" + std::to_string(getRandomInt());
        ArithmeticTask* result = new ArithmeticTask(op, arg1, arg2, name);
        m_tasks.addLast(result);
        return result;
    }

    AddTask* createAddTask() {
        Container<Task*>* container = createAndFillTaskContainer();
        Task* task = createArithmeticTask();
        AddTask* result = new AddTask(*container, *task);
        m_tasks.addLast(result);
        return result;
    }

    
    SizeTask* createSizeTask() {
        Container<Object*>* container = createAndFillObjectContainer();
        SizeTask* result = new SizeTask(*container);
        m_tasks.addLast(result);
        return result;
    }

    CleanTask* createCleanTask() {
        Container<Object*>* container = createAndFillObjectContainer();
        CleanTask* result = new CleanTask(*container);
        m_tasks.addLast(result);
        return result;
    }

    ObjectCountTask* createObjectCountTask() {
        ObjectCountTask* result = new ObjectCountTask();
        m_tasks.addLast(result);
        return result;
    }

    Task* createRandomTask() {
        switch (std::rand() % 5) {
        case 0: return createArithmeticTask();
        case 1: return createAddTask();
        case 2: return createSizeTask();
        case 3: return createCleanTask();
        case 4: return createObjectCountTask();
        default: return nullptr;
        }
    }

private:
    Container<Task*>* createAndFillTaskContainer() {
        Container<Task*>* container = new Container<Task*>;
        for (int i = 0; i < getRandomInt(); i++) {
            container->addLast(createArithmeticTask());
        }
        m_taskContainers.addLast(container);
        return container;
    }

    Container<Object*>* createAndFillObjectContainer() {
        Container<Object*>* container = new Container<Object*>;
        for (int i = 0; i < getRandomInt(); i++) {
            container->addLast(createArithmeticTask());
        }
        m_objectContainers.addLast(container);
        return container;
    }

    int getRandomInt() {
        return std::rand() % 100;
    }

    Container<Container<Task*>*> m_taskContainers;
    Container<Container<Object*>*> m_objectContainers;
    Container<Task*> m_tasks;
};
