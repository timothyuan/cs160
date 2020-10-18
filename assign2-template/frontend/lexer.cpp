#include "frontend/lexer.h"
#include <iostream>

namespace cs160::frontend {

void DFA::add_transitions(char a, char b, int start, int end){
  while (a <= b) {
    if(transitions[start].find(a)==transitions[start].end()){
      transitions[start][a] = end;
    }
    a++;
  }
}

int DFA::delta(int state, char a){
  try{
    return transitions[state].at(a);
  }catch(...){
    return -1;
  }
}

bool DFA::isAccepted(int state){
  try{
    accept.at(state);
    return true;
  }catch(...){
    return false;
  }
}

DFA::DFA(){
  transitions[0]= {
    {'i',1},
    {'e',6},
    {'w',10},
    {'f',15},
    {'t',21},
    {'d',23},
    {'r',26},
    {'o',32},
    {'(',38},
    {')',39},
    {'[',40},
    {']',41},
    {'{',42},
    {'}',43},
    {'-',45},
    {'+',46},
    {'*',46},
    {';',47},
    {':',48},
    {',',50},
    {'!',51},
    {'<',52},
    {'&',54},
    {'|',56},
    {'/',58},
    {' ',60},{'\n',60},{'\t',60},
    {'=', 61}
  };
  add_transitions('a','z',0,4);
  add_transitions('A','Z',0,4);
  add_transitions('0','9',0,44);

  accept[1] = std::optional<TokenType>(TokenType::Id);
  transitions[1] = {{'f',2},{'n',3}};
  add_transitions('a','z',1,4);
  add_transitions('A','Z',1,4);
  add_transitions('0','9',1,4);

  accept[2] = std::optional<TokenType>(TokenType::If);
  add_transitions('a','z',2,4);
  add_transitions('A','Z',2,4);
  add_transitions('0','9',2,4);

  accept[3] = std::optional<TokenType>(TokenType::Id);
  transitions[3] = {{'t',5}};
  add_transitions('a','z',3,4);
  add_transitions('A','Z',3,4);
  add_transitions('0','9',3,4);

  accept[4] = std::optional<TokenType>(TokenType::Id);
  add_transitions('a','z',4,4);
  add_transitions('A','Z',4,4);
  add_transitions('0','9',4,4);

  accept[5] = std::optional<TokenType>(TokenType::Type);
  add_transitions('a','z',5,4);
  add_transitions('A','Z',5,4);
  add_transitions('0','9',5,4);

  accept[6] = std::optional<TokenType>(TokenType::Id);
  transitions[6] = {{'l',7}};
  add_transitions('a','z',6,4);
  add_transitions('A','Z',6,4);
  add_transitions('0','9',6,4);

  accept[7] = std::optional<TokenType>(TokenType::Id);
  transitions[7] = {{'s',8}};
  add_transitions('a','z',7,4);
  add_transitions('A','Z',7,4);
  add_transitions('0','9',7,4);

  accept[8] = std::optional<TokenType>(TokenType::Id);
  transitions[8] = {{'e',9}};
  add_transitions('a','z',8,4);
  add_transitions('A','Z',8,4);
  add_transitions('0','9',8,4);

  accept[9] = std::optional<TokenType>(TokenType::Else);
  add_transitions('a','z',9,4);
  add_transitions('A','Z',9,4);
  add_transitions('0','9',9,4);

  accept[10] = std::optional<TokenType>(TokenType::Id);
  transitions[10] = {{'h',11}};
  add_transitions('a','z',10,4);
  add_transitions('A','Z',10,4);
  add_transitions('0','9',10,4);

  accept[11] = std::optional<TokenType>(TokenType::Id);
  transitions[11] = {{'i',12}};
  add_transitions('a','z',11,4);
  add_transitions('A','Z',11,4);
  add_transitions('0','9',11,4);

  accept[12] = std::optional<TokenType>(TokenType::Id);
  transitions[12] = {{'l',13}};
  add_transitions('a','z',12,4);
  add_transitions('A','Z',12,4);
  add_transitions('0','9',12,4);

  accept[13] = std::optional<TokenType>(TokenType::Id);
  transitions[13] = {{'e',14}};
  add_transitions('a','z',13,4);
  add_transitions('A','Z',13,4);
  add_transitions('0','9',13,4);

  accept[14] = std::optional<TokenType>(TokenType::While);
  add_transitions('a','z',14,4);
  add_transitions('A','Z',14,4);
  add_transitions('0','9',14,4);

  accept[15] = std::optional<TokenType>(TokenType::Id);
  transitions[15] = {{'o',16}, {'r',17}};
  add_transitions('a','z',15,4);
  add_transitions('A','Z',15,4);
  add_transitions('0','9',15,4);

  accept[16] = std::optional<TokenType>(TokenType::Id);
  transitions[16] = {{'r',20}};
  add_transitions('a','z',16,4);
  add_transitions('A','Z',16,4);
  add_transitions('0','9',16,4);

  accept[17] = std::optional<TokenType>(TokenType::Id);
  transitions[17] = {{'o',18}};
  add_transitions('a','z',17,4);
  add_transitions('A','Z',17,4);
  add_transitions('0','9',17,4);

  accept[18] = std::optional<TokenType>(TokenType::Id);
  transitions[18] = {{'m',19}};
  add_transitions('a','z',18,4);
  add_transitions('A','Z',18,4);
  add_transitions('0','9',18,4);

  accept[19] = std::optional<TokenType>(TokenType::From);
  add_transitions('a','z',19,4);
  add_transitions('A','Z',19,4);
  add_transitions('0','9',19,4);

  accept[20] = std::optional<TokenType>(TokenType::For);
  add_transitions('a','z',20,4);
  add_transitions('A','Z',20,4);
  add_transitions('0','9',20,4);

  accept[21] = std::optional<TokenType>(TokenType::Id);
  transitions[21] = {{'o',22}};
  add_transitions('a','z',21,4);
  add_transitions('A','Z',21,4);
  add_transitions('0','9',21,4);

  accept[22] = std::optional<TokenType>(TokenType::To);
  add_transitions('a','z',22,4);
  add_transitions('A','Z',22,4);
  add_transitions('0','9',22,4);

  accept[23] = std::optional<TokenType>(TokenType::Id);
  transitions[23] = {{'e',24}};
  add_transitions('a','z',23,4);
  add_transitions('A','Z',23,4);
  add_transitions('0','9',23,4);

  accept[24] = std::optional<TokenType>(TokenType::Id);
  transitions[24] = {{'f',25}};
  add_transitions('a','z',24,4);
  add_transitions('A','Z',24,4);
  add_transitions('0','9',24,4);

  accept[25] = std::optional<TokenType>(TokenType::Def);
  add_transitions('a','z',25,4);
  add_transitions('A','Z',25,4);
  add_transitions('0','9',25,4);

  accept[26] = std::optional<TokenType>(TokenType::Id);
  transitions[26] = {{'e',27}};
  add_transitions('a','z',26,4);
  add_transitions('A','Z',26,4);
  add_transitions('0','9',26,4);

  accept[27] = std::optional<TokenType>(TokenType::Id);
  transitions[27] = {{'t',28}};
  add_transitions('a','z',27,4);
  add_transitions('A','Z',27,4);
  add_transitions('0','9',27,4);

  accept[28] = std::optional<TokenType>(TokenType::Id);
  transitions[28] = {{'u',29}};
  add_transitions('a','z',28,4);
  add_transitions('A','Z',28,4);
  add_transitions('0','9',28,4);

  accept[29] = std::optional<TokenType>(TokenType::Id);
  transitions[29] = {{'r',30}};
  add_transitions('a','z',29,4);
  add_transitions('A','Z',29,4);
  add_transitions('0','9',29,4);

  accept[30] = std::optional<TokenType>(TokenType::Id);
  transitions[30] = {{'n',31}};
  add_transitions('a','z',30,4);
  add_transitions('A','Z',30,4);
  add_transitions('0','9',30,4);

  accept[31] = std::optional<TokenType>(TokenType::Return);
  add_transitions('a','z',31,4);
  add_transitions('A','Z',31,4);
  add_transitions('0','9',31,4);

  accept[32] = std::optional<TokenType>(TokenType::Id);
  transitions[32] = {{'u',33}};
  add_transitions('a','z',32,4);
  add_transitions('A','Z',32,4);
  add_transitions('0','9',32,4);

  accept[33] = std::optional<TokenType>(TokenType::Id);
  transitions[33] = {{'t',34}};
  add_transitions('a','z',33,4);
  add_transitions('A','Z',33,4);
  add_transitions('0','9',33,4);

  accept[34] = std::optional<TokenType>(TokenType::Id);
  transitions[34] = {{'p',35}};
  add_transitions('a','z',34,4);
  add_transitions('A','Z',34,4);
  add_transitions('0','9',34,4);

  accept[35] = std::optional<TokenType>(TokenType::Id);
  transitions[35] = {{'u',36}};
  add_transitions('a','z',35,4);
  add_transitions('A','Z',35,4);
  add_transitions('0','9',35,4);

  accept[36] = std::optional<TokenType>(TokenType::Id);
  transitions[36] = {{'t',37}};
  add_transitions('a','z',36,4);
  add_transitions('A','Z',36,4);
  add_transitions('0','9',36,4);

  accept[37] = std::optional<TokenType>(TokenType::Output);
  add_transitions('a','z',37,4);
  add_transitions('A','Z',37,4);
  add_transitions('0','9',37,4);

  accept[30] = std::optional<TokenType>(TokenType::Id);
  transitions[30] = {{'n',31}};
  add_transitions('a','z',30,4);
  add_transitions('A','Z',30,4);
  add_transitions('0','9',30,4);

  accept[38] = std::optional<TokenType>(TokenType::LParen);
  accept[39] = std::optional<TokenType>(TokenType::RParen);
  accept[40] = std::optional<TokenType>(TokenType::LBracket);
  accept[41] = std::optional<TokenType>(TokenType::RBracket);
  accept[42] = std::optional<TokenType>(TokenType::LBrace);
  accept[43] = std::optional<TokenType>(TokenType::RBrace);

  accept[44] = std::optional<TokenType>(TokenType::Num);
  add_transitions('0','9',44,44);

  accept[45] = std::optional<TokenType>(TokenType::ArithOp);
  add_transitions('0','9',45,44);

  accept[46] = std::optional<TokenType>(TokenType::ArithOp);
  accept[47] = std::optional<TokenType>(TokenType::Semicolon);

  accept[48] = std::optional<TokenType>(TokenType::HasType);
  transitions[48] = {{'=',49}};

  accept[49] = std::optional<TokenType>(TokenType::Assign);
  accept[50] = std::optional<TokenType>(TokenType::Comma);
  accept[51] = std::optional<TokenType>(TokenType::LNeg);

  accept[52] = std::optional<TokenType>(TokenType::RelOp);
  transitions[52] = {{'=',53}};

  accept[53] = std::optional<TokenType>(TokenType::RelOp);

  transitions[54] = {{'&',55}};

  accept[55] = std::optional<TokenType>(TokenType::LBinOp);

  transitions[56] = {{'|',57}};

  accept[57] = std::optional<TokenType>(TokenType::LBinOp);

  transitions[58] = {{'/',59}};

  transitions[59] = {{'\n',60}};
  add_transitions(char(0), char(255), 59, 59);

  accept[60] = std::optional<TokenType>();
  transitions[60] = {{' ',60},{'\n',60},{'\t',60}};

  accept[61] = std::optional<TokenType>(TokenType::RelOp);
}

std::vector<Token> Lexer::tokenize(const std::string & programText) {
  std::vector<Token> result;
  DFA dfa = DFA();
  int curr_state = 0;
  size_t curr_input_pos = 0;
  size_t curr_scan_pos = 0;
  int curr_accepted_pos = -1;
  int accepting_state = 0;

  while(curr_scan_pos<programText.size()){
    curr_state = dfa.delta(curr_state, programText[curr_scan_pos]);
    curr_scan_pos++;

    if(curr_state!=-1&&dfa.isAccepted(curr_state)){
      curr_accepted_pos = curr_scan_pos;
      accepting_state = curr_state;
    }

    if(curr_state==-1||curr_scan_pos==programText.size()){
      if(curr_accepted_pos==-1){
        throw InvalidLexemeError();
      }else{
        curr_scan_pos = curr_accepted_pos;
        curr_accepted_pos = -1;
        std::string info = programText.substr(curr_input_pos, curr_scan_pos-curr_input_pos);
        std::optional<TokenType> type = dfa.accept[accepting_state];

        try {
          switch(type.value()){
            case TokenType::Id:
              result.push_back(Token::makeId(info));
              break;
            case TokenType::Num:
              result.push_back(Token::makeNum(std::stoi(info)));
              break;
            case TokenType::Type:
              result.push_back(Token::makeType(info));
              break;
            case TokenType::If:
              result.push_back(Token::makeIf());
              break;
            case TokenType::Else:
              result.push_back(Token::makeElse());
              break;
            case TokenType::While:
              result.push_back(Token::makeWhile());
              break;
            case TokenType::Def:
              result.push_back(Token::makeDef());
              break;
            case TokenType::Return:
              result.push_back(Token::makeReturn());
              break;
            case TokenType::Output:
              result.push_back(Token::makeOutput());
              break;
            case TokenType::ArithOp:
              if(info == "+") result.push_back(Token::makeArithOp(ArithOp::Plus));
              else if(info == "*") result.push_back(Token::makeArithOp(ArithOp::Times));
              else if(info == "-") result.push_back(Token::makeArithOp(ArithOp::Minus));
              break;
            case TokenType::RelOp:
              if(info == "<") result.push_back(Token::makeRelOp(RelOp::LessThan));
              else if(info == "<=") result.push_back(Token::makeRelOp(RelOp::LessEq));
              else if(info == "=") result.push_back(Token::makeRelOp(RelOp::Equal));
              break;
            case TokenType::LBinOp:
              if(info == "&&") result.push_back(Token::makeLBinOp(LBinOp::And));
              else if(info == "||") result.push_back(Token::makeLBinOp(LBinOp::Or));
              break;
            case TokenType::LNeg:
              result.push_back(Token::makeLNeg());
              break;
            case TokenType::LParen:
              result.push_back(Token::makeLParen());
              break;
            case TokenType::RParen:
              result.push_back(Token::makeRParen());
              break;
            case TokenType::LBrace:
              result.push_back(Token::makeLBrace());
              break;
            case TokenType::RBrace:
              result.push_back(Token::makeRBrace());
              break;
            case TokenType::Semicolon:
              result.push_back(Token::makeSemicolon());
              break;
            case TokenType::Assign:
              result.push_back(Token::makeAssign());
              break;
            case TokenType::HasType:
              result.push_back(Token::makeHasType());
              break;
            case TokenType::Comma:
              result.push_back(Token::makeComma());
              break;
            case TokenType::RBracket:
              result.push_back(Token::makeRBracket());
              break;
            case TokenType::LBracket:
              result.push_back(Token::makeLBracket());
              break;
            case TokenType::For:
              result.push_back(Token::makeFor());
              break;
            case TokenType::From:
              result.push_back(Token::makeFrom());
              break;
            case TokenType::To:
              result.push_back(Token::makeTo());
              break;
          }
        }catch(...){
          
        }
        curr_state = 0;
        curr_input_pos = curr_scan_pos;
      }
    }
  }
  return result;
}

}  // namespace cs160::frontend
