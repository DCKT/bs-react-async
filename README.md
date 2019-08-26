# bs-react-async

🚧 Partial BuckleScript bindings for react-async v8. This will be updated if needed.

## Install

```
yarn add @dck/bs-react-async
```

Add it to `bs-dependencies` in your `bsconfig.json` :

```json
{
  "bs-dependencies": ["@dck/bs-react-async"]
}
```

## Usage

### Basic

```reason
open BsReactAsync;

let fetchSomeData = () => serviceThatReturnAPromise();

[@react.component]
let make = () => {
  let request = ReactAsync.useAsync(fetchSomeData, ());
  let isLoading = request->ReactAsync.Req.isLoading;
  let error = request->ReactAsync.Req.error->Js.Nullable.toOption;
  let data = request->ReactAsync.Req.data;

  {
    switch (isLoading, error, data) {
      | (true, _, _) => <p>"Loading"->React.string</p>
      | (false, Some(e), _) => <p>
        {
          error
            ->Js.Exn.message
            ->Belt.Option.getWithDefault("An error occured")
            |> React.string
        }
      </p>
      | (false, None, data) => {
        Js.log(data);

        <div>
          "show data"->React.string
        </div>
      }
    }
  }
};
```

### Components

```reason
open BsReactAsync;

let fetchSomeData = () => serviceThatReturnAPromise();

[@react.component]
let make = () => {
  let request = ReactAsync.useAsync(fetchSomeData, ());


  <>
    <Pending state=request>
      <p>"Loading"->React.string</p>
    </Pending>
    <Rejected state=request>
      {
        error =>
      <p>
        {
          error
            ->Js.Exn.message
            ->Belt.Option.getWithDefault("An error occured")
            |> React.string
        }
      </p>
      }
    </Rejected>
    <Fulfilled state=request>
      {
        data => {
          Js.log(data);

          <div>
            "show data"->React.string
          </div>
        }
      }
    </Fulfilled>
  </>
};
```
