// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.8.2 <0.9.0;

contract MiniSocial {

    uint256 public TWEET_MAX_LENGTH = 300;

    struct Post {
        uint256 id;
        address author;
        string content;
        uint256 timestamp;
        uint256 likes;
    }

    mapping ( address => Post[] ) Posts;

    function publishPost(string memory _message) public {
        require ( bytes(_message).length <= TWEET_MAX_LENGTH, "tweet is to long");

        Post memory newPost = Post({
            id: Posts[msg.sender].length,
            author: msg.sender,
            content: _message,
            timestamp: block.timestamp,
            likes: 0
        });

        Posts[msg.sender].push(newPost);
    }

    function getPost(uint256 _index) public view returns (string memory, address){
        return (Posts[msg.sender][_index].content, Posts[msg.sender][_index].author);
    }

    function getAllTweets (address _author) public view returns (Post[] memory){
            return Posts[_author];
    }
}