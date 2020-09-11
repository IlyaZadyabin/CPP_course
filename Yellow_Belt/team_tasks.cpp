#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

using TasksInfo = map<TaskStatus, int>;


void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		 ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		 ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		 ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return developers.at(person);
	}

	void AddNewTask(const string& person) {
		developers[person][TaskStatus::NEW]++;
	}

	void erase_empty_key(TasksInfo & dict) {
		vector<TaskStatus> tmp;
		for (auto & [info, cnt] : dict) {
			if (cnt == 0) {
				tmp.push_back(info);
			}
		}
		for (auto item : tmp) {
			dict.erase(item);
		}
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo update, nonUpdate;
		if (developers.find(person) != developers.end()) {
			TasksInfo tmp = developers[person];
			nonUpdate = tmp;
			nonUpdate.erase(TaskStatus::DONE);
			int cnt, tasks_to_shift = 0;

			for (auto i = static_cast<int>(TaskStatus::NEW); i < static_cast<int>(TaskStatus::DONE); ++i) {
				auto info = static_cast<TaskStatus>(i);
				cnt = developers[person][info];
				tmp[info] += tasks_to_shift;
				update[info] += tasks_to_shift;
				tasks_to_shift = 0;
				if (task_count > 0) {
					task_count -= cnt;
					tasks_to_shift = task_count >= 0 ? cnt : task_count + cnt;
					nonUpdate[info] -= tasks_to_shift;
					tmp[info] -= tasks_to_shift;
				}
			}
			tmp[TaskStatus::DONE] += tasks_to_shift;
			update[TaskStatus::DONE] += tasks_to_shift;
			developers[person] = tmp;
			erase_empty_key(developers[person]);
		}
		erase_empty_key(update);
		erase_empty_key(nonUpdate);
		return make_tuple(update, nonUpdate);
	}
private:
	map<string, TasksInfo> developers;
};

void print_updates(TeamTasks & tasks, int task_cnt) {
	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", task_cnt);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	cout << endl;
}

int main()
{
	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	cout << "Alice's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	for (int i = 0; i < 2; i++) {
		print_updates(tasks, 5);
	}
	print_updates(tasks, 1);

	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	print_updates(tasks, 2);

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	print_updates(tasks, 4);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
}
