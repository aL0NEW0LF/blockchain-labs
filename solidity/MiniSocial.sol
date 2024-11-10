// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

contract Twitter{

    address public owner;
    uint256 public TWEET_MAX_LENGTH = 300;
    
    struct Tweet {
        uint256 id;
        address author;
        string content;
        uint256 timestamp;
        uint256 likes;
        uint256 dislikes;
        bool isDeleted;
    }

    constructor(){
        owner = msg.sender;
    }

    mapping (address => Tweet[]) tweets;
    mapping(uint => mapping(address => bool)) public Liked;
    mapping(uint => mapping(address => bool)) public Disliked;


    event TweetCreated(uint256 id, address author, string content, uint256 timestamp, uint256 likes);
    event TweetLiked (address liker, address tweetAuthot, uint256 id, uint256 newLikeCount);
    event TweetUnLiked (address unLiker, address tweetAuthot, uint256 id, uint256 newLikeCount);

    function createTweet(string memory _tweet) public {
        
        require ( bytes(_tweet).length <= TWEET_MAX_LENGTH, "tweet is to long");

        Tweet memory newTweet = Tweet({
            id: tweets[msg.sender].length,
            author: msg.sender,
            content: _tweet,
            timestamp: block.timestamp,
            likes: 0,
            dislikes: 0,
            isDeleted: false
        });
            
        tweets[msg.sender].push(newTweet); 

        emit TweetCreated(newTweet.id, newTweet.author, newTweet.content, newTweet.timestamp, newTweet.likes);   
    }

    function likeTweet (address author, uint256 id) external {
        require(!Liked[id][msg.sender], "You have already liked or disliked this tweet");

        Liked[id][msg.sender] = true;
        Disliked[id][msg.sender] = false;
        tweets[author][id].likes++;
        tweets[author][id].dislikes--;

        emit TweetLiked(msg.sender, author, id, tweets[author][id].likes);
    }

    function unLikeTweet(address author, uint256 id) external {
        require(!Disliked[id][msg.sender], "You have not liked this tweet or have already disliked it");

        Disliked[id][msg.sender] = true;
        Liked[id][msg.sender] = false;
        tweets[author][id].likes--;
        tweets[author][id].dislikes++;

        emit TweetUnLiked(msg.sender, author, id, tweets[author][id].likes);
    } 


    modifier onlyOwner(){
        require(msg.sender == owner, "ONLY THE OWNER CAN DO THIS");
        _;
    }

    modifier onlyAuthor(uint256 _index, address _author){
        require(msg.sender == tweets[_author][_index].author, "Only tweet author can do this");
        _;
    }

    function changeTweetLength (uint256 _newTweetLength) public onlyOwner {
        TWEET_MAX_LENGTH = _newTweetLength;
    }

    function getTweet ( uint _i) public view returns (Tweet memory){
        return tweets[msg.sender][_i];
    }   

    function getAllTweets (address author) public view returns (Tweet[] memory){
        return tweets[author];
    }

    function deleteTweet(uint256 id, address author) external onlyAuthor(id, author) {
        require(_exists(id), "Tweet does not exist");
        
        delete tweets[author][id];
        tweets[author][id].isDeleted = true;
    }

    function _exists (uint256 id) internal view returns (bool){
        return getAllTweets(msg.sender).length > id;
    }

    function modifyTweet (address author, uint256 id, string memory _tweetContent ) external onlyAuthor(id, author) {
        require(_exists(id), "Tweet does not exist");
        require ( bytes(_tweetContent).length <= TWEET_MAX_LENGTH, "tweet is to long" );
    
        tweets[author][id].content = _tweetContent;
    }
}