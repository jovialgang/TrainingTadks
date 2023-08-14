#ifndef RESULTCODE_H
#define RESULTCODE_H


enum class ResultCode {
    Success,
    NoPointFound,
    EndStartPointError,
    NotEnoughValidPointsFound,
    NeedAtLeastTwoValues,
    ErrorTooManyPoints,
    InvalidPointValues,
    Error3,
};

#endif // RESULTCODE_H
