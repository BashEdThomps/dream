#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace octronic::dream
{
    /**
     * @brief The TaskQueue class is responsible for scheduling and executing
     * Tasks that are used to implement a Project's runtime logic.
     *
     * Tasks will be pushed by the pushTasks method of the following classes.
     * @see AssetRuntime::pushTasks
     * @see Component::pushTasks
     *
     * Tasks are owned by their parent Object and stored as shared_ptr<...>
     * TaskQueue will NOT delete tasks;
     *
     * ProjectRuntime owns the TaskQueue and DestructionTaskQueue. The
     * ProjectRuntime::step function will submit all Tasks for
     * SharedAssetInstances held by their respective Components.
     *
     * for each component:
     *     for each runtime:
     *			runtime->pushTasks()
     *
     * SceneRuntime will submit all Tasks for DiscreteAssetInstances owned by
     * Entities the Entities tree.
     *
     * Graphics-related tasks extend the GraphicsTask or GraphicsDestructionTask class.
     * These MUST BE executed on the main thread. Their execution is handled by the
     * GraphicsComponent (OpenGL threading limitation, yes I know about Vulcan).
     *
     */

	template <typename TaskType>
	class TaskQueue
	{
	public:
		TaskQueue(const string& className);
		void pushTask(const TaskType& t);
		void executeQueue();
		bool hasTask(const TaskType& t) const;
		vector<TaskType>* getTaskQueue() const;
		size_t getTaskCount() const;
	private:
		vector<TaskType> mQueue;
        string mClassName;
	};
}

// Template Implementation
#include "TaskQueue.tpp"
