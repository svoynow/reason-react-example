/* ReasonReact used by ReactJS */
/* This is just a normal stateless component. The only change you need to turn
   it into a ReactJS-compatible component is the wrapReasonForJs call below */
let component = ReasonReact.statelessComponent("PageReason");

let make = (~message, ~extraGreeting=?, _children) => {
  ...component,
  render: _self => {
    let greeting =
      switch (extraGreeting) {
      | None => "How are you?"
      | Some(g) => g
      };
    <div> <MyBannerRe show=true message=(message ++ " " ++ greeting) /> </div>;
  },
};

[@bs.deriving abstract]
type jsProps = {
  message: string,
  extraGreeting: Js.nullable(string),
};

/* This exposes a `jsComponent` that the ReactJS side can use as
   require('greetingRe.js').jsComponent

   if **you know what you're doing** and have
   the correct babel/webpack setup, you can also do `let default = ...` and use it
   on the JS side as a default export. */
let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~message=jsProps |. message,
      ~extraGreeting=?Js.Nullable.toOption(jsProps |. extraGreeting),
      [||],
    )
  );
