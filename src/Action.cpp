#include "Action.h"
#include <iostream>
#include "Studio.h"


////
//
//class:BaseAction
//TODO: check for diffrent initalization in constructor
BaseAction::BaseAction(){};
ActionStatus BaseAction::getStatus() const{
    return status;
};
void BaseAction::complete(){
    status = COMPLETED;
}
//TODO: need to complete method implenation
void BaseAction::error(std::string errorMsg){
    this->errorMsg=errorMsg;
}
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}

// class:openTrainer

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id),customers(customersList){
        //TODO: we need to decide if to deep copy the customers or not
        BaseAction::error("Workout session does not exist or is already open.");
        // we need to make sure if the customers can be init in the init list?
        // for(Customer* cus_1 : customersList){
        //     Customer* x = cus_1;
        //     customers.push_back(x);
        // }
};
void OpenTrainer::act( Studio& studio){
    Trainer* t = studio.getTrainer(trainerId);
    if (t==nullptr||t->isOpen())
        std::cout<<BaseAction::getErrorMsg()<<endl;
    else {
        t->openTrainer();
        int counter = 0,length = customers.size(),capacity = t->getCapacity();
         for (size_t i = 0; i < capacity; i++)
         {
             t->addCustomer(customers[i]);
         }
    }
    //need to delete pointer??
    // delete t;
};
std::string OpenTrainer::toString() const{};


// class:Order
/*
in the constructor:
update the trainer id
in act:
need to check if the trainer dosent exist or isnt open
we proably need to use the trainer order method so it can:
use the costumer method of order and to print the workout for each one
we need to think about how to save the data for future need
*/

Order::Order(int id):trainerId(id){
    BaseAction::error("Trainer does not exist or is not open");
};
void Order::act(Studio &studio){
    Trainer* t = studio.getTrainer(trainerId);
    //checking for error: null or nullptr???
    if(t==nullptr)
        std::cout<< BaseAction::getErrorMsg()<<endl;
    else{
        std::vector<Workout>& Workout_options= studio.getWorkoutOptions();
        std::vector <Customer*>& customers = t->getCustomers();
        for(Customer* c : customers){
            //using the customer order method and sending it to the trainer order method
            t->order(c->getId(),c->order(Workout_options),Workout_options);
        }
        std::vector<OrderPair>& orders = t->getOrders();
        //printing the orders:
        for(OrderPair order : orders){
            if(order.first != -1)
                std::cout<< t->getCustomer(order.first)->getName() + "Is Doing" + order.second.getName()<<endl;
        }
    }
    delete t;
}
//keeping implenation for the actions log
std::string Order::toString() const{

}


// class MoveCustomer:
/*
in the constructor:
upadate the fields
in the act:
check all the bad cases
lets say we have the source costumer = 1 and the dest =2
we want to do 2.addCustomer(1.getCustomer(id))
then we want to do 1.removeCustomer(id)
we need to implement those methods in trainer correctly according to this
after that we need to check all the bad cases that might have happend
like an empty trainer
we need to remember to transfer the order in the order
*/
MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src),dstTrainer(dst),id(customerId){
    BaseAction::error("Cannot move customer");
    }
void MoveCustomer::act(Studio &Studio){
    bool valid = true;
    //check if 1.src or dst dont exist or closed,
    //2.customer don't belong to src tranier
    // 3.dst trainer is full
    Trainer* dst = Studio.getTrainer(srcTrainer);
    Trainer* src = Studio.getTrainer(dstTrainer);
    if(dst==NULL || !dst->isOpen() || src==NULL || !src->isOpen()||!src->isCustomerOfTrainer(id)
    ||dst->isFull())
        valid = false;
    if(!valid)
        std::cout<< BaseAction::getErrorMsg()<<endl;
    else{
    Customer* customer = src->getCustomer(id);
    //add the customer to the dst trainer
    dst->addCustomer(customer);
    //add the customer orders to the new trainer
    vector<Workout>& workout_options=Studio.getWorkoutOptions();
    vector<int> workouts_ids = customer->order(workout_options);
    dst->order(id,workouts_ids,workout_options);
    //remove the customer from the src trainer
    src->removeCustomer(id);
    //check if the src trainer is empty
    if(src->isEmpty())
        src->closeTrainer();
    }

};
//keeping implentation for the actions log
std::string MoveCustomer::toString() const{};

/*

class close:

in the constructor=
usual
in the act:
salary - uses the getSalary method of the trainer(which sums the vector)

class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};
*/
Close::Close(int id):trainerId(id){
    BaseAction::error("Trainer does not exist or is not open");
};
void Close::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    //TODO: check if the trainer dosent exist or isnt open
    if(trainer == nullptr || !trainer->isOpen())
        std::cout<<getErrorMsg()<<endl;
    else{
    trainer->closeTrainer();
    int salary = trainer->getSalary();
    std::cout<< "Trainer "<< trainerId<<" closed. Salary "<< salary<<"NIS"<<endl;
    }

}
//TODO
std::string Close::toString()const{};


CloseAll::CloseAll(){};

void CloseAll::act(Studio &studio){
    studio.close();
};
//TODO
std::string CloseAll::toString() const{};


/*
class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
private:
};
*/
PrintWorkoutOptions::PrintWorkoutOptions(){};
void PrintWorkoutOptions::act(Studio &studio){
    vector<Workout> workout_options = studio.getWorkoutOptions();
    for(Workout workout : workout_options){
        std::cout<<workout.getName()<<", "<<workout.getType()<<", "<<workout.getPrice()<<endl;
    }
}
//TODO:
std::string PrintWorkoutOptions::toString() const{};


/*
class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};
*/

PrintTrainerStatus::PrintTrainerStatus(int id):trainerId(id){
    // TODO: do we need to add an error? its not mentioned in the question specificly
};
void PrintTrainerStatus::act(Studio &studio){
    Trainer *trainer =studio.getTrainer(trainerId);
    //TODO : print error if needed
    if(trainer != nullptr && trainer->isOpen()){
        //TODO: how do we print a trainer status??
        //std::cout<< "Trainer "<<trainer.get
        vector<Customer*> customers = trainer->getCustomers();
        for(Customer* c: customers){
            //TODO: print customer
        }
        vector<OrderPair>& orders = trainer->getOrders();
        for(OrderPair order : orders){
            //TODO: print order
        }
    }
}

