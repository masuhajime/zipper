#ifndef ZIPPER_RANKING_H
#define ZIPPER_RANKING_H

namespace zipper
{
    class Ranking
    {
    public:
        static bool postScore(std::string application_id, std::string rest_api_key, int score);
        //static bool getScore(std::string application_id, std::string rest_api_key, int score);
    };

} // namespace zipper

#endif /* ZIPPER_RANKING_H */
