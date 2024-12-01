
State::HUNGRY

void test(size_t i) 
// if philosopher i is hungry and both neighbors are not
// eating then eat
{ 
    // i: philosopher number, from 0 to N-1
    if (state[i] == State::HUNGRY &&
        state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING) 
    {
        state[i] = State::EATING;
        both_forks_available[i].release(); // forks are no longer needed for this eat session
    }
}