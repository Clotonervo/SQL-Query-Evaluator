/*
Lex.cpp
*/

#include "Lex.h"

//----------------------------------------- Constructors ---------------------------------------
Lex::Lex()
{
    istream = new InputStream("none");
    isString = false;
    isComment = false;
    lineMarker = -1;
}

Lex::Lex(string inputString)
{
    istream = new InputStream(inputString);
    isString = false;
    isComment = false;
    lineMarker = 0;
}

//----------------------------------------- Destructor ---------------------------------------
Lex::~Lex()
{
    delete istream;
}

//----------------------------------------- Creating Tokens ---------------------------------------
void Lex::CreateToken(TokenType type, string tokenString)
{
    tokenList.push_back(Token(type, tokenString, istream->GetCurrentLineNumber()));
    return;
}

void Lex::CreateMultiLineToken(TokenType type, string tokenString, int beginLineNum)
{
    tokenList.push_back(Token(type, tokenString, lineMarker));
    return;
}

//--------------------------------------------------------------------------------------------------------------------------
//                                  START STATE
//--------------------------------------------------------------------------------------------------------------------------
                                                                                                                                    
void Lex::StartState()
{
    if (istream->endOfFile){
        EndOfFileState();
        return;
    }
    else if (isalpha(istream->CurrentChar())){
        IDState();
    }
   else if (isspace(istream->CurrentChar())){
       istream->Advance();
   }
   else if (!isalnum(istream->CurrentChar())){
       CharacterState();
   }
   else {
       ErrorState();
   }
    
    StartState();
}

void Lex::CharacterState()
{
    if (istream->CurrentChar() == ','){
        CommaState();
    }
    else if (istream->CurrentChar() == '.'){
        PeriodState();
    }
    else if (istream->CurrentChar() == '?'){
        QMarkState();
    }
    else if (istream->CurrentChar() == '('){
        LeftParenState();
    }
    else if (istream->CurrentChar() == ')'){
        RightParenState();
    }
    else {
        CharacterStatePartTwo();
    }
    return;
}

void Lex::CharacterStatePartTwo()
{
    if (istream->CurrentChar() == ':'){
        ColonState();
    }
    else if (istream->CurrentChar() == '*'){
        MultiplyState();
    }
    else if (istream->CurrentChar() == '+'){
        AddState();
    }
    else if (istream->CurrentChar() == '\''){
        StringState();
    }
    else if (istream->CurrentChar() == '#'){
        CommentState();
    }
    else {
        ErrorState();
    }
    return;
}

//--------------------------------------------------------------------------------------------------------------------------
//                                      Simple States
//--------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------COMMA---------------------------------------
void Lex::CommaState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(COMMA,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------PERIOD---------------------------------------
void Lex::PeriodState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(PERIOD,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------Q MARK---------------------------------------
void Lex::QMarkState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(Q_MARK,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------L PAREN---------------------------------------
void Lex::LeftParenState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(LEFT_PAREN,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------R PAREN---------------------------------------
void Lex::RightParenState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(RIGHT_PAREN,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------COLON---------------------------------------
void Lex::ColonState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (istream->CurrentChar() == '-'){
        ColonDashState();
    }
    else {
        CreateToken(COLON, valueSoFar);
        valueSoFar = "";
    }
    return;
}

//-----------------------------------------COLON DASH---------------------------------------
void Lex::ColonDashState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(COLON_DASH,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------MULTIPLY---------------------------------------
void Lex::MultiplyState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(MULTIPLY,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//-----------------------------------------ADD---------------------------------------
void Lex::AddState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    CreateToken(ADD,valueSoFar);
    istream->Advance();
    valueSoFar = "";

    return;
}

//--------------------------------------------------------------------------------------------------------------------------
//                               Schemes, Facts, Rules, Queries
//--------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------SCHEMES---------------------------------------
void Lex::SchemesState()
{
    if (valueSoFar == "Schemes"){
        CreateToken(SCHEMES, valueSoFar);
        valueSoFar = "";
    }
    else {
        FactsState();
    }
   
    return;
}

//-----------------------------------------FACTS---------------------------------------
void Lex::FactsState()
{
    if (valueSoFar == "Facts"){
        CreateToken(FACTS, valueSoFar);
        valueSoFar = "";
    }
    else {
        RulesState();
    }
    return;
}

//-----------------------------------------RULES---------------------------------------
void Lex::RulesState()
{
    if (valueSoFar == "Rules"){
        CreateToken(RULES, valueSoFar);
        valueSoFar = "";
    }
    else {
        QueriesState();
    }
    return;
}

//-----------------------------------------QUERIES---------------------------------------
void Lex::QueriesState()
{
    if (valueSoFar == "Queries"){
        CreateToken(QUERIES, valueSoFar);
        valueSoFar = "";
    }
    else {
        CreateToken(ID, valueSoFar);
        valueSoFar = "";
    }
    return;
}


//--------------------------------------------------------------------------------------------------------------------------
//                                      More Complicated States
//--------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------ID---------------------------------------
void Lex::IDState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (isdigit(istream->CurrentChar())){
        IDState();
    }
    else if (isalpha(istream->CurrentChar())){
        IDState();
    }
    else {
        SchemesState();
    }
    return;
}

//-----------------------------------------STRING---------------------------------------


void Lex::StringState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (istream->CurrentChar() == '\''){
        valueSoFar = valueSoFar + istream->CurrentChar();
        EndStringState();
    }
    else if (istream->endOfFile){
        ErrorState();
    }
    else if (istream->CurrentChar() == '\n'){
        if (!isString){
            lineMarker = istream->GetCurrentLineNumber();
        }
        isString = true;
        StringState();
    }
    else {
        StringState();
    }
    return;
}

void Lex::EndStringState()
{
    istream->Advance();
    if (istream->CurrentChar() == '\''){
        StringState();
    }
    else if (isString){
        CreateMultiLineToken(STRING, valueSoFar, lineMarker);
        isString = false;
        valueSoFar = "";
    }
    else {
        CreateToken(STRING, valueSoFar);
        valueSoFar = "";
    }
    return;
}


//-----------------------------------------COMMENT---------------------------------------


void Lex::CommentState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (istream->CurrentChar() == '|'){
        BlockCommentState();
    }
    else if ((istream->CurrentChar() == '\n') | istream->endOfFile){
        CreateToken(COMMENT, valueSoFar);
        istream->Advance();
        valueSoFar = "";
        return;
    }
    else {
        SingleLineState();
    }
    return;
}

void Lex::SingleLineState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if ((istream->CurrentChar() == '\n') | (istream->endOfFile)){
       // CreateToken(COMMENT, valueSoFar);
        valueSoFar = "";
        return;
    }
    else {
        SingleLineState();
    }
    return;
}

void Lex::BlockCommentState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (istream->CurrentChar() == '|'){
        SawBarState();
    }
    else if (istream->endOfFile){
        ErrorState();
    }
    else if (istream->CurrentChar() == '\n'){
        if (!isComment){
            lineMarker = istream->GetCurrentLineNumber();
        }
        isComment = true;
        BlockCommentState();
    }
    else {
        BlockCommentState();
    }
    return;
}

void Lex::SawBarState()
{
    valueSoFar = valueSoFar + istream->CurrentChar();
    istream->Advance();
    if (istream->CurrentChar() == '#'){
        valueSoFar = valueSoFar + istream->CurrentChar();
        if (isComment){
          //  CreateMultiLineToken(COMMENT, valueSoFar, lineMarker);
        }
        else{
          //  CreateToken(COMMENT, valueSoFar);
        }
        valueSoFar = "";
        isComment = false;
        if (!istream->endOfFile){
            istream->Advance();
        }
        return;
    }
    else if (istream->endOfFile){
        ErrorState();
    }
    else {
        BlockCommentState();
    }
    return;
}


//-----------------------------------------UNDEFINED---------------------------------------
void Lex::ErrorState()
{
    if (isString){
        CreateMultiLineToken(UNDEFINED, valueSoFar, lineMarker);
        isString = false;
    }
    else if (isComment){
        CreateMultiLineToken(UNDEFINED, valueSoFar, lineMarker);
        isComment = false;
    }
    else {
        valueSoFar = valueSoFar + istream->CurrentChar();
        CreateToken(UNDEFINED,valueSoFar);
        istream->Advance();
    }
    valueSoFar = "";
    return;
}

//-----------------------------------------END OF FILE---------------------------------------
void Lex::EndOfFileState()
{
    if (isComment){
        BlockCommentState();
    }
    else if (isString){
        StringState();
    }
    CreateToken(END_OF_FILE, "");
    return;
}












