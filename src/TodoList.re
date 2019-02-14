type action =
  | UpdateInput(string)
  | AddItem;

type item = string;

type state = {
  items: list(item),
  inputValue: string,
};

let component = ReasonReact.reducerComponent("TodoList");

let renderInput = (value, send) => {
  <input
    type_="text"
    value
    onChange={event => {
      let newValue = ReactEvent.Form.target(event)##value;
      send(UpdateInput(newValue));
    }}
  />;
};

let renderItem = item => {
  <li> {ReasonReact.string(item)} </li>;
};

let renderTodoList = items => {
  <ul>
    {items |> List.map(renderItem) |> Array.of_list |> ReasonReact.array}
  </ul>;
};

let renderButton = send => {
  <button onClick={event => send(AddItem)}>
    {ReasonReact.string("Add Item")}
  </button>;
};

let make = _children => {
  ...component,
  initialState: () => {items: [], inputValue: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateInput(newInput) =>
      ReasonReact.Update({...state, inputValue: newInput})
    | AddItem =>
      ReasonReact.Update({...state, items: [state.inputValue] @ state.items})
    },
  render: ({state, send}) => {
    ReasonReact.array([|
      renderInput(state.inputValue, send),
      renderButton(send),
      renderTodoList(state.items),
    |]);
  },
};
