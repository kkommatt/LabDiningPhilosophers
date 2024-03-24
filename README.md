# LabDiningPhilosophers
Develop and program an algorithm for solving Dining philosophers.
The solution should: get resource exclusivity (fork as a resource can be taken only by one (out of two neighboring) philosophers at each moment of time, and only if it is free)
deadlock-free (so that the system cannot deadlock)
livelock-free (so that philosophers do not die of starvation, when they do not manage to take from where for a long time, because they are blocked by something by their neighbors), a situation of endless waiting
Preference is given to a solution that:
implement one algorithm of actions of all philosophers (do not depend on the number of the philosopher, etc.)
do not have a centralized entity (waiter, oracle, etc.) that manages the distribution of video resources
do not provide for communication between philosophies (for them to agree on where from or other joint actions)
is scalable to any number of philosophers (and views accordingly) and has no obvious bottlenecks
it is possible to formally prove their correctness and fulfillment of all requirements
All philosopher programs must follow the same algorithm. They are all equal (and interchangeable), none has priority over the others.
